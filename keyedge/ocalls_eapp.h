#include "eapp_utils.h"
#include "edge_call.h"
#include <syscall.h>
#include "ocalls.h"
#include "ocalls_common.h"
#include "ocalls_builder.h"
#include "ocalls_reader.h"
unsigned long print_buffer(char *str) {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	size_t __0_str_keyedge_size = strlen(str) + 1;
	flatbuffers_int8_vec_ref_t __flatcc_reference_str;
	{
		char* __keyedge_array_data_1 = (char*) malloc((1 * (__0_str_keyedge_size)) * sizeof(char));
		for (size_t i1 = 0; i1 < (size_t) (__0_str_keyedge_size); ++i1) {
			{
				__keyedge_array_data_1[i1 + (__0_str_keyedge_size) * (0)] = str[i1];
			}
		}
		__flatcc_reference_str = flatbuffers_int8_vec_create(&builder, (signed char*)__keyedge_array_data_1, 1 * (__0_str_keyedge_size));
		free(__keyedge_array_data_1);
	}
	__ocall_wrapper_print_buffer_start_as_root(&builder);
	__ocall_wrapper_print_buffer_str_add(&builder, __flatcc_reference_str);
	__ocall_wrapper_print_buffer_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	char return_address[1024];
	ocall(__function_print_buffer, __buf, __size, return_address, 1024);
	free(__buf);
	flatcc_builder_clear(&builder);
	unsigned long __return_value;
	{
		__return_value = __ocall_wrapper_print_buffer___return_value(__ocall_wrapper_print_buffer_as_root(return_address));
	}
	return __return_value;
}
void print_value(unsigned long val) {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	unsigned long __flatcc_reference_val;
	{
		__flatcc_reference_val = val;
	}
	__ocall_wrapper_print_value_start_as_root(&builder);
	__ocall_wrapper_print_value_val_add(&builder, __flatcc_reference_val);
	__ocall_wrapper_print_value_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	char return_address[1024];
	ocall(__function_print_value, __buf, __size, return_address, 1024);
	free(__buf);
	flatcc_builder_clear(&builder);
}
void send_reply(void *message, unsigned long len) {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	unsigned long __flatcc_reference_len;
	{
		__flatcc_reference_len = len;
	}
	flatbuffers_int8_vec_ref_t __flatcc_reference_message;
	{
		char* __keyedge_array_data_1 = (char*) malloc((1 * (len)) * sizeof(char));
		for (size_t i1 = 0; i1 < (size_t) (len); ++i1) {
			{
				__keyedge_array_data_1[i1 + (len) * (0)] = ((char*) message)[i1];
			}
		}
		__flatcc_reference_message = flatbuffers_int8_vec_create(&builder, (signed char*)__keyedge_array_data_1, 1 * (len));
		free(__keyedge_array_data_1);
	}
	__ocall_wrapper_send_reply_start_as_root(&builder);
	__ocall_wrapper_send_reply_message_add(&builder, __flatcc_reference_message);
	__ocall_wrapper_send_reply_len_add(&builder, __flatcc_reference_len);
	__ocall_wrapper_send_reply_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	char return_address[1024];
	ocall(__function_send_reply, __buf, __size, return_address, 1024);
	free(__buf);
	flatcc_builder_clear(&builder);
}
void send_report(void *shared_buffer, unsigned long len) {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	unsigned long __flatcc_reference_len;
	{
		__flatcc_reference_len = len;
	}
	flatbuffers_int8_vec_ref_t __flatcc_reference_shared_buffer;
	{
		char* __keyedge_array_data_1 = (char*) malloc((1 * (len)) * sizeof(char));
		for (size_t i1 = 0; i1 < (size_t) (len); ++i1) {
			{
				__keyedge_array_data_1[i1 + (len) * (0)] = ((char*) shared_buffer)[i1];
			}
		}
		__flatcc_reference_shared_buffer = flatbuffers_int8_vec_create(&builder, (signed char*)__keyedge_array_data_1, 1 * (len));
		free(__keyedge_array_data_1);
	}
	__ocall_wrapper_send_report_start_as_root(&builder);
	__ocall_wrapper_send_report_shared_buffer_add(&builder, __flatcc_reference_shared_buffer);
	__ocall_wrapper_send_report_len_add(&builder, __flatcc_reference_len);
	__ocall_wrapper_send_report_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	char return_address[1024];
	ocall(__function_send_report, __buf, __size, return_address, 1024);
	free(__buf);
	flatcc_builder_clear(&builder);
}
pubkey *wait_for_client_pubkey() {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_wait_for_client_pubkey_start_as_root(&builder);
	__ocall_wrapper_wait_for_client_pubkey_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	char return_address[1024];
	ocall(__function_wait_for_client_pubkey, __buf, __size, return_address, 1024);
	free(__buf);
	flatcc_builder_clear(&builder);
	pubkey *__return_value;
	{
		if (__pointer_pubkey___is_null(__ocall_wrapper_wait_for_client_pubkey___return_value(__ocall_wrapper_wait_for_client_pubkey_as_root(return_address)))) {
			__return_value = 0;
		} else {
			__return_value = (pubkey *) malloc(sizeof(pubkey));
			{
				{
					for (size_t i4 = 0; i4 < (size_t) (32); ++i4) {
						{
							(*__return_value).data[i4] = flatbuffers_int8_vec_at(pubkey_data(__pointer_pubkey___data(__ocall_wrapper_wait_for_client_pubkey___return_value(__ocall_wrapper_wait_for_client_pubkey_as_root(return_address)))), i4 + (32) * (0));
						}
					}
				}
			}
		}
	}
	return __return_value;
}
encl_message_t wait_for_message() {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_wait_for_message_start_as_root(&builder);
	__ocall_wrapper_wait_for_message_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	char return_address[1024];
	ocall(__function_wait_for_message, __buf, __size, return_address, 1024);
	free(__buf);
	flatcc_builder_clear(&builder);
	encl_message_t __return_value;
	{
		{
			__return_value.len = encl_message_t_len(__ocall_wrapper_wait_for_message___return_value(__ocall_wrapper_wait_for_message_as_root(return_address)));
		}
		{
			__return_value.host_ptr = (void *) malloc((__return_value.len) * sizeof(char));
			for (size_t i2 = 0; i2 < (size_t) (__return_value.len); ++i2) {
				{
					((char*) __return_value.host_ptr)[i2] = flatbuffers_int8_vec_at(encl_message_t_host_ptr(__ocall_wrapper_wait_for_message___return_value(__ocall_wrapper_wait_for_message_as_root(return_address))), i2 + (__return_value.len) * (0));
				}
			}
		}
	}
	return __return_value;
}
