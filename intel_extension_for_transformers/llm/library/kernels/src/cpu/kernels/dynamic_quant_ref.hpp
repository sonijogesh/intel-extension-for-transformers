//  Copyright (c) 2022 Intel Corporation
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef ENGINE_SPARSELIB_SRC_CPU_KERNELS_DYNAMIC_QUANT_REF_HPP_
#define ENGINE_SPARSELIB_SRC_CPU_KERNELS_DYNAMIC_QUANT_REF_HPP_

#include "kernel.hpp"
#include "kernel_desc.hpp"
#include "kernels/exposed_enum.hpp"
#include "operator_desc.hpp"
#include "src/cpu/cpu_isa.hpp"
#include "src/utils.hpp"
#include <functional>
#include <glog/logging.h>
#include <memory>
#include <vector>

namespace jd {
class dynamic_quant_ref_k_t;

class SPARSE_TEST_API_ dynamic_quant_ref_kd_t : public kernel_desc_t {
public:
  explicit dynamic_quant_ref_kd_t(const operator_desc &op_desc)
      : kernel_desc_t(kernel_kind::dynamic_quant), op_desc_(op_desc) {}

  virtual ~dynamic_quant_ref_kd_t() {}

public:
  bool init() override { return true; };
  DECLARE_COMMON_PD_T(dynamic_quant_ref_k_t, dynamic_quant_ref_kd_t);

public:
  inline std::vector<dim_t> shape() const {
    return op_desc_.tensor_descs()[0].shape();
  }
  const operator_desc &get_operator_desc() const override { return op_desc_; }

private:
  operator_desc op_desc_;
};

class SPARSE_TEST_API_ dynamic_quant_ref_k_t : public kernel_t {
public:
  using kd_t = dynamic_quant_ref_kd_t;
  explicit dynamic_quant_ref_k_t(const std::shared_ptr<const kd_t> &kd)
      : kernel_t(kd) {}
  virtual ~dynamic_quant_ref_k_t() {}
  // Delete move constructor and move operator
  dynamic_quant_ref_k_t(dynamic_quant_ref_k_t &&other) = delete;
  dynamic_quant_ref_k_t &operator=(dynamic_quant_ref_k_t &&other) = delete;
  // Delete copy constructor and copy operator
  dynamic_quant_ref_k_t(const dynamic_quant_ref_k_t &other) = delete;
  dynamic_quant_ref_k_t &operator=(const dynamic_quant_ref_k_t &other) = delete;

public:
  bool init() override { return true; };

  bool execute(const std::vector<const void *> &rt_data) const override;

public:
  const std::shared_ptr<const kd_t> derived_kd() const {
    return std::static_pointer_cast<const kd_t>(kd_);
  }
};

} // namespace jd
#endif
