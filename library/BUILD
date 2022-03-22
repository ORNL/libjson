# libjson Bazel BUILD file

cc_library(
	name = "libjson",
	srcs = glob(["*.cpp","powers.hpp"]),
	hdrs= ["libjson.hpp"],
	visibility = ["//visibility:public"]
)

cc_test(
	name = "libjson_test",
	size = "small",
	tags = ["unit"],
	srcs = ["test/libjson_test.cpp"],
	deps = [":libjson"],
	includes = ["."],
	data = [
        "//library:test/test_basic.json",
        "//library:test/test_array_complex.json"
    ],
)

