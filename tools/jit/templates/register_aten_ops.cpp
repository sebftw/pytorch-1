#include "torch/csrc/jit/operator.h"
#include "torch/csrc/jit/custom_operator.h"

#include "torch/csrc/autograd/profiler.h"
#include "torch/csrc/autograd/generated/variable_factories.h"

#include <ATen/ATen.h>
#include <ATen/core/functional.h>
#include <ATen/core/interned_strings.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// ${generated_comment}

// NOTE [Sharded File]: This file is generated in a sharded fashion to speed up
// incremental rebuilds. See the comment at the top of
// templates/VariableType.cpp for an analogous, in-depth discussion.
//
// Note that unlike VariableType.cpp, when sharding this file we take
// care to generate all overloads of a particular name in a single
// file and in a particular order. See gen_jit_dispatch.py for
// details.

namespace torch { namespace jit {

using autograd::Variable;
using autograd::variable_list;
using at::Scalar;
using at::ScalarType;
using at::Tensor;
using at::TensorOptions;
using at::DeviceGuard;

using ::c10::fmap;
using ::c10::filter;

namespace {

inline at::optional<at::Device> deviceForInputs(Stack & stack, size_t N) {
  if(N == 0)
    return c10::nullopt;
  auto t = (stack.end() - N)->toTensor();
  return c10::make_optional(t.device());
}

template<size_t N>
std::array<bool, N> as_bool_array(const std::vector<bool>& vec) {
  std::array<bool, N> res;
  AT_ASSERT(vec.size() == N);
  std::copy(vec.begin(), vec.end(), res.begin());
  return res;
}

RegisterOperators reg({
  Operator(
  "aten::get_device(Tensor self) -> int",
  [](Stack & stack) {
      autograd::profiler::RecordFunction record("get_device");
      auto result = at::get_device(
          (std::move(peek(stack, 0, 1))).toTensor()
      );
      drop(stack, 1);
      pack(stack, std::move(result));
      return 0;
  }
  ),
  Operator(
      "aten::storage_offset(Tensor self) -> int",
      [](Stack & stack) {
          autograd::profiler::RecordFunction record("storage_offset");
          auto result = ((std::move(peek(stack, 0, 1))).toTensor()).storage_offset();
          drop(stack, 1);
          pack(stack, std::move(result));
          return 0;
      }
  ),

  // Generated operators
  ${constructors}
});

} // anon namespace


}} // namespace torch::jit
