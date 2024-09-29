# idf_component_register(
#     SRC_DIRS
#         "."
#         "app"
#     INCLUDE_DIRS
#         "."
#         "app")


idf_component_register(
    SRC_DIRS
    "."
    INCLUDE_DIRS
    "."
)

component_compile_options(-ffast-math -O3 -Wno-error=format -Wno-format)

