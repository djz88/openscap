/*
 * test_probes.c
 *
 *  Created on: Aug 4, 2009
 *      Author: Peter Vrabec
 */

#include <stdio.h>
#include <stdlib.h>
#include "api/oval_agent_api.h"

int _test_error_handler(struct oval_xml_error *error, void *null)
{
	//ERROR HANDLING IS TODO
	return 1;
}

void oval_syschar_to_print(struct oval_syschar*, const char*, int);

int main(int argc, char **argv)
{
	struct oval_definition_model *model = oval_definition_model_new();

	struct oval_import_source *is = oval_import_source_new_file(argv[1]);
	oval_definition_model_load(model, is, &_test_error_handler, NULL);
	oval_import_source_free(is);

	struct oval_object_iterator *objects = oval_definition_model_get_objects(model);
	if (!oval_object_iterator_has_more(objects)) {
		printf("NO DEFINITIONS FOUND\n");
		return 1;
	}

	int index;
	for (index = 1; oval_object_iterator_has_more(objects); index++) {
		struct oval_object *object = oval_object_iterator_next(objects);
		oval_object_to_print(object, "    ", index);
		printf("Callin probe on object\n");
		struct oval_syschar* syschar = oval_object_probe(object, model);
		printf("System characteristics:\n");
		if (syschar)
			oval_syschar_to_print(syschar, "    ", index);
		else
			printf("(NULL)\n");
	}

	return 0;
}

