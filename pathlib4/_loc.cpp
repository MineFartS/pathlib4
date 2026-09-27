#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <filesystem>
#include <string>

#include "remap.h"

class _loc { public:

    str temp() {
        pyobj gettempdir = import("tempfile").attr("gettempdir");

        str SRV = "E:/__temp__/";
        str OS  = gettempdir().cast<str>();
        
        std::error_code ec;
        return fs::exists(SRV, ec) ? SRV : OS;
    }

    fs::path script() {

        py::object mod = import("sys").attr("modules")["__main__"];

        fs::path pure;

        if (py::hasattr(mod, "__file__")) {
            str _file = mod.attr("__file__").cast<str>();
            pure = fs::path(_file).parent_path();
        } else {
            pure = fs::current_path();
        }

        return pure;
    }

    fs::path cache() {
        return this->script() / "/__pycache__/";
    }

};

PYBIND11_MODULE(_loc, m) {

    py::class_<_loc>(m, "_loc")
        .def(py::init<>())
        .def_property_readonly("temp", &_loc::temp)
        .def_property_readonly("script", &_loc::script)
        .def_property_readonly("cache", &_loc::cache);

}

