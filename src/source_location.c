#include "source_location.h"

yyjson_mut_val *source_location_py_to_json(PyObject *source_location_object,
                                           yyjson_mut_doc *doc) {
  char *file_id;
  Py_ssize_t begin_offset, end_offset;

  PyArg_ParseTuple(source_location_object, "snn", &file_id, &begin_offset,
                   &end_offset);

  yyjson_mut_val *file_id_json = yyjson_mut_str(doc, file_id);
  yyjson_mut_val *begin_offset_json =
      yyjson_mut_uint(doc, (uint32_t)begin_offset);
  yyjson_mut_val *end_offset_json = yyjson_mut_uint(doc, (uint32_t)end_offset);

  yyjson_mut_val *source_location_json = yyjson_mut_arr(doc);
  yyjson_mut_arr_append(source_location_json, file_id_json);
  yyjson_mut_arr_append(source_location_json, begin_offset_json);
  yyjson_mut_arr_append(source_location_json, end_offset_json);

  return source_location_json;
}
