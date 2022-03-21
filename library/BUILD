# libjson Bazel BUILD file

cc_library(
	name = "libjson",
	srcs = glob(["*.cpp","fpconv.hpp","powers.hpp"]),
	hdrs= ["libjson.hpp"],
	visibility = ["//visibility:public"]
)

cc_test(
	name = "libjson_test",
	srcs = ["test/libjson_test.cpp"],
	deps = [":libjson"],
	includes = ["."]
)

