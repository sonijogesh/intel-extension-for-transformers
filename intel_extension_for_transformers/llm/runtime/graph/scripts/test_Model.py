import numpy as np
from intel_extension_for_transformers.llm.runtime.graph import Model
model = Model()

weights = np.array([1.0, 2.0, 3.0, 4.0, 5.0], dtype=np.float32)
scales = np.array([1.0, 2.0, 3.0, 4.0, 5.0], dtype=np.float32)
dst = np.array([1.0, 2.0, 3.0, 4.0, 5.0], dtype=np.float32)

import pdb; pdb.set_trace()
model.init_from_bin("mpt", "/mnt/disk2/data/zhenweil/codes/ggml/mpt_ne.bin", max_new_tokens=20, num_beams=1, do_sample=True, top_k=40, top_p=0.95)
model.model.numpy_to_float_ptr(weights, scales, dst)

# 打印C++函数返回的指针值
print(dst)

