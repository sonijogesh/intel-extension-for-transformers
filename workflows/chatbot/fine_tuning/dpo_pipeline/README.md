Direct Preference Optimization (DPO)
============

For Better aligning human preferences, we apply Direct Preference Optimization (DPO) algorithm, which is stable and computationally lightweight. The algorithm derives the probability of human preference data for the optimal policy to replace the reward model that reinforcement learning from human feedback (RLHF) needs and formulates a maximum likelihood objective for a parameterized policy. For more details of DPO, you can refer [Direct Preference Optimization: Your Language Model is Secretly a Reward Model](https://arxiv.org/pdf/2305.18290.pdf).

## 1. Environment

```shell
pip install -r requirements.txt
```

## 2. Prepare reference dataset

We select 12k examples from [Orca](https://arxiv.org/abs/2306.02707) style dataset [Open-Orca/OpenOrca](https://huggingface.co/datasets/Open-Orca/OpenOrca), and regard its completions that are generated from GPT-4 or GPT-3.5 as chosen response. Simply and automatically, we use llama-2-13b-chat model to generate corresponding reject responses. For details of the dataset, you can refer [Intel/orca_dpo_pairs](https://huggingface.co/datasets/Intel/orca_dpo_pairs)


## 3. Training

```
python dpo_clm.py --model_name_or_path "mosaicml/mpt-7b" --output_dir "mpt_7b-dpo" --per_device_train_batch_size 1 --gradient_accumulation_steps 8 --learning_rate 5e-4 --max_steps 1000 --save_steps 10 --lora_alpha 16 --lora_rank 16 --lora_dropout 0.05 --dataset_name Intel/orca_dpo_pairs --bf16 --use_auth_token True
```


## 4. Evaluation

We verify DPO training on our finetuned `mpt-7b` model [Intel/neural-chat-7b-v1-1](https://huggingface.co/Intel/neural-chat-7b-v1-1). The evaluation metrics is same as [open_llm_leaderboard](https://huggingface.co/spaces/HuggingFaceH4/open_llm_leaderboard) which uses [Eleuther AI Language Model Evaluation Harness](https://github.com/EleutherAI/lm-evaluation-harness/tree/master), a unified framework to test generative language models on a large number of different evaluation tasks.

#### mpt architecture
| Model | Average ⬆️| ARC (25-s) ⬆️ | HellaSwag (10-s) ⬆️ | MMLU (5-s) ⬆️| TruthfulQA (MC) (0-s) ⬆️ | Evaluation by |
| --- | --- | --- | --- | --- | --- | --- |
|[mosaicml/mpt-7b](https://huggingface.co/mosaicml/mpt-7b)| 47.4  | 47.61 | 77.56 | 31 | 33.43 | ours |
| [mosaicml/mpt-7b-chat](https://huggingface.co/mosaicml/mpt-7b-chat) | 49.95 | 46.5 | 75.55 | 37.60 | 40.17 | ours |
| [Intel/neural-chat-7b-v1-1](https://huggingface.co/Intel/neural-chat-7b-v1-1) | **51.41**   | 50.09 | 76.69 | 38.79 | 40.07 | ours |
| **[Intel/neural-chat-7b-v1-1](https://huggingface.co/Intel/neural-chat-7b-v1-1) with DPO** | **52.39** | 51.54  | 76.45 | 39.47| 42.10 | ours |


