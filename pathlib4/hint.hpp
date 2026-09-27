#pragma once

#include <pybind11/pybind11.h>

struct PathTypeHint {
    py::object i;
};

namespace pybind11 { namespace detail {
    template <> struct type_caster<PathTypeHint> {
    public:
        PYBIND11_TYPE_CASTER(PathTypeHint, const_name("Path"));

        static handle cast(PathTypeHint src, return_value_policy /* policy */, handle /* parent */) {
            return src.i.release();
        }
    };
}}
