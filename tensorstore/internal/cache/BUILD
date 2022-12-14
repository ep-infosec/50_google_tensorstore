load("//bazel:tensorstore.bzl", "tensorstore_cc_binary", "tensorstore_cc_library", "tensorstore_cc_test")
load("@bazel_skylib//rules:common_settings.bzl", "bool_flag")

package(
    default_visibility = ["//tensorstore:internal_packages"],
)

licenses(["notice"])

bool_flag(
    name = "async_cache_debug",
    build_setting_default = False,
)

config_setting(
    name = "async_cache_debug_setting",
    flag_values = {
        ":async_cache_debug": "True",
    },
    visibility = ["//visibility:private"],
)

# To enable debug logging, specify:
# bazel build --//tensorstore/internal/cache:async_cache_debug
tensorstore_cc_library(
    name = "async_cache",
    srcs = ["async_cache.cc"],
    hdrs = ["async_cache.h"],
    defines = select({
        ":async_cache_debug_setting": ["TENSORSTORE_ASYNC_CACHE_DEBUG"],
        "//conditions:default": [],
    }),
    deps = [
        ":cache",
        "//tensorstore:transaction",
        "//tensorstore/internal:intrusive_linked_list",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:intrusive_red_black_tree",
        "//tensorstore/internal:logging",
        "//tensorstore/internal:mutex",
        "//tensorstore/internal:no_destructor",
        "//tensorstore/internal:source_location",
        "//tensorstore/internal:tagged_ptr",
        "//tensorstore/internal:type_traits",
        "//tensorstore/kvstore:generation",
        "//tensorstore/util:future",
        "//tensorstore/util:quote_string",
        "//tensorstore/util:result",
        "//tensorstore/util:status",
        "//tensorstore/util/execution:any_receiver",
        "//tensorstore/util/execution:sender",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/synchronization",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/utility",
    ],
)

tensorstore_cc_test(
    name = "async_cache_test",
    size = "small",
    srcs = ["async_cache_test.cc"],
    deps = [
        ":async_cache",
        ":cache",
        "//tensorstore/internal:concurrent_testutil",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:memory",
        "//tensorstore/internal:queue_testutil",
        "//tensorstore/kvstore:generation",
        "//tensorstore/kvstore:generation_testutil",
        "//tensorstore/util:future",
        "//tensorstore/util:result",
        "//tensorstore/util:status",
        "//tensorstore/util:status_testutil",
        "@com_google_absl//absl/time",
        "@com_google_googletest//:gtest_main",
    ],
)

tensorstore_cc_library(
    name = "async_initialized_cache_mixin",
    hdrs = ["async_initialized_cache_mixin.h"],
    deps = [
        ":cache",
        "//tensorstore/util:future",
    ],
)

tensorstore_cc_library(
    name = "kvs_backed_cache",
    hdrs = ["kvs_backed_cache.h"],
    deps = [
        ":async_cache",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore:generation",
        "//tensorstore/util:assert_macros",
        "//tensorstore/util:future",
        "//tensorstore/util:status",
        "//tensorstore/util/execution",
        "//tensorstore/util/execution:future_sender",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings:cord",
        "@com_google_absl//absl/time",
    ],
)

tensorstore_cc_test(
    name = "kvs_backed_cache_test",
    size = "small",
    srcs = ["kvs_backed_cache_test.cc"],
    deps = [
        ":async_cache",
        ":cache",
        ":kvs_backed_cache",
        ":kvs_backed_cache_testutil",
        "//tensorstore:transaction",
        "//tensorstore/internal:global_initializer",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore:mock_kvstore",
        "//tensorstore/kvstore:test_util",
        "//tensorstore/kvstore/memory",
        "//tensorstore/util:status_testutil",
        "@com_google_googletest//:gtest_main",
    ],
)

tensorstore_cc_library(
    name = "kvs_backed_cache_testutil",
    testonly = True,
    srcs = ["kvs_backed_cache_testutil.cc"],
    hdrs = ["kvs_backed_cache_testutil.h"],
    deps = [
        ":async_cache",
        ":cache",
        ":kvs_backed_cache",
        "//tensorstore:transaction",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:logging",
        "//tensorstore/internal:mutex",
        "//tensorstore/internal:source_location",
        "//tensorstore/internal:test_util",
        "//tensorstore/kvstore",
        "//tensorstore/kvstore:generation",
        "//tensorstore/kvstore:generation_testutil",
        "//tensorstore/kvstore:key_range",
        "//tensorstore/kvstore:test_util",
        "//tensorstore/util:assert_macros",
        "//tensorstore/util:future",
        "//tensorstore/util:quote_string",
        "//tensorstore/util:result",
        "//tensorstore/util:status",
        "//tensorstore/util:status_testutil",
        "//tensorstore/util:str_cat",
        "//tensorstore/util/execution",
        "//tensorstore/util/execution:sender",
        "@com_google_absl//absl/random",
        "@com_google_absl//absl/random:bit_gen_ref",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:cord",
        "@com_google_absl//absl/time",
        "@com_google_googletest//:gtest",
    ],
)

tensorstore_cc_library(
    name = "aggregate_writeback_cache",
    hdrs = ["aggregate_writeback_cache.h"],
    deps = [
        ":async_cache",
        ":cache",
        "//tensorstore/internal/estimate_heap_usage",
    ],
)

tensorstore_cc_library(
    name = "cache",
    srcs = [
        "cache.cc",
        "cache_impl.h",
    ],
    hdrs = [
        "cache.h",
        "cache_pool_limits.h",
    ],
    deps = [
        "//tensorstore/internal:heterogeneous_container",
        "//tensorstore/internal:integer_overflow",
        "//tensorstore/internal:intrusive_linked_list",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:mutex",
        "//tensorstore/internal/poly",
        "//tensorstore/util:assert_macros",
        "@com_google_absl//absl/base",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/functional:function_ref",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/synchronization",
    ],
)

tensorstore_cc_library(
    name = "cache_pool_resource",
    srcs = ["cache_pool_resource.cc"],
    hdrs = ["cache_pool_resource.h"],
    deps = [
        ":cache",
        "//tensorstore:context",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal/json_binding",
        "//tensorstore/internal/json_binding:bindable",
        "//tensorstore/util:result",
        "@com_github_nlohmann_json//:nlohmann_json",
    ],
    alwayslink = 1,
)

tensorstore_cc_test(
    name = "cache_pool_resource_test",
    size = "small",
    srcs = ["cache_pool_resource_test.cc"],
    deps = [
        ":cache",
        ":cache_pool_resource",
        "//tensorstore:context",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/util:result",
        "//tensorstore/util:status",
        "//tensorstore/util:status_testutil",
        "@com_github_nlohmann_json//:nlohmann_json",
        "@com_google_googletest//:gtest_main",
    ],
)

tensorstore_cc_test(
    name = "cache_test",
    size = "small",
    timeout = "moderate",
    srcs = [
        "cache_test.cc",
    ],
    deps = [
        ":cache",
        "//tensorstore/internal:concurrent_testutil",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:memory",
        "//tensorstore/util:str_cat",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/synchronization",
        "@com_google_googletest//:gtest_main",
    ],
)

tensorstore_cc_library(
    name = "chunk_cache",
    srcs = ["chunk_cache.cc"],
    hdrs = ["chunk_cache.h"],
    deps = [
        ":async_cache",
        ":cache",
        "//tensorstore:array",
        "//tensorstore:box",
        "//tensorstore:contiguous_layout",
        "//tensorstore:data_type",
        "//tensorstore:index",
        "//tensorstore:rank",
        "//tensorstore:staleness_bound",
        "//tensorstore:strided_layout",
        "//tensorstore:transaction",
        "//tensorstore/driver",
        "//tensorstore/driver:chunk",
        "//tensorstore/index_space:index_transform",
        "//tensorstore/index_space:transformed_array",
        "//tensorstore/internal:arena",
        "//tensorstore/internal:async_write_array",
        "//tensorstore/internal:elementwise_function",
        "//tensorstore/internal:grid_partition",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:memory",
        "//tensorstore/internal:mutex",
        "//tensorstore/internal:nditerable",
        "//tensorstore/util:element_pointer",
        "//tensorstore/util:extents",
        "//tensorstore/util:future",
        "//tensorstore/util:iterate",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:status",
        "//tensorstore/util/execution",
        "//tensorstore/util/execution:any_receiver",
        "//tensorstore/util/execution:sender",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/container:fixed_array",
        "@com_google_absl//absl/container:inlined_vector",
        "@com_google_absl//absl/status",
    ],
)

tensorstore_cc_binary(
    name = "chunk_cache_benchmark_test",
    testonly = 1,
    srcs = ["chunk_cache_benchmark_test.cc"],
    tags = ["benchmark"],
    deps = [
        ":async_cache",
        ":cache",
        ":chunk_cache",
        "//tensorstore:array",
        "//tensorstore:box",
        "//tensorstore:contiguous_layout",
        "//tensorstore:data_type",
        "//tensorstore:index",
        "//tensorstore:progress",
        "//tensorstore:rank",
        "//tensorstore/driver",
        "//tensorstore/index_space:dim_expression",
        "//tensorstore/index_space:index_transform",
        "//tensorstore/index_space:transformed_array",
        "//tensorstore/internal:element_copy_function",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:thread_pool",
        "//tensorstore/kvstore:generation",
        "//tensorstore/util:executor",
        "//tensorstore/util:future",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:status",
        "//tensorstore/util:str_cat",
        "@com_google_absl//absl/container:inlined_vector",
        "@com_google_absl//absl/time",
        "@com_google_benchmark//:benchmark",
        "@com_google_benchmark//:benchmark_main",  # build_cleaner: keep
    ],
)

tensorstore_cc_test(
    name = "chunk_cache_test",
    size = "small",
    srcs = ["chunk_cache_test.cc"],
    deps = [
        ":async_cache",
        ":cache",
        ":chunk_cache",
        ":kvs_backed_cache",
        "//tensorstore",
        "//tensorstore:array",
        "//tensorstore:box",
        "//tensorstore:data_type",
        "//tensorstore:index",
        "//tensorstore:progress",
        "//tensorstore:rank",
        "//tensorstore:staleness_bound",
        "//tensorstore/driver",
        "//tensorstore/driver:chunk",
        "//tensorstore/index_space:dim_expression",
        "//tensorstore/index_space:index_transform",
        "//tensorstore/index_space:transformed_array",
        "//tensorstore/internal:element_copy_function",
        "//tensorstore/internal:elementwise_function",
        "//tensorstore/internal:intrusive_ptr",
        "//tensorstore/internal:masked_array",
        "//tensorstore/internal:memory",
        "//tensorstore/internal:meta",
        "//tensorstore/internal:queue_testutil",
        "//tensorstore/internal:thread_pool",
        "//tensorstore/kvstore:generation",
        "//tensorstore/kvstore:mock_kvstore",
        "//tensorstore/kvstore:test_util",
        "//tensorstore/kvstore/memory",
        "//tensorstore/util:executor",
        "//tensorstore/util:future",
        "//tensorstore/util:result",
        "//tensorstore/util:span",
        "//tensorstore/util:status",
        "//tensorstore/util:status_testutil",
        "//tensorstore/util/execution:sender",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:inlined_vector",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
        "@com_google_googletest//:gtest_main",
    ],
)
