#include <keystone.h>
#include <edge_call.h>
#include "ocalls.h"
#include "ocalls_common.h"
#include "ocalls_builder.h"
#include "ocalls_reader.h"
void __wrapper_print_buffer(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	char *str;
	__ocall_wrapper_print_buffer_table_t function_reference = __ocall_wrapper_print_buffer_as_root((void *) call_args);
	flatbuffers_int8_vec_t __flatcc_reference_str = __ocall_wrapper_print_buffer_str(function_reference);
	size_t __0_str_keyedge_size = flatbuffers_int8_vec_len(__flatcc_reference_str);
	{
		str = (char *) malloc((__0_str_keyedge_size) * sizeof(char));
		for (size_t i1 = 0; i1 < (size_t) (__0_str_keyedge_size); ++i1) {
			{
				str[i1] = flatbuffers_int8_vec_at(__flatcc_reference_str, i1 + (__0_str_keyedge_size) * (0));
			}
		}
	}
	unsigned long ret_val;
	ret_val = print_buffer(str);
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_print_buffer_start_as_root(&builder);
	unsigned long __flatcc_reference_ret_val;
	{
		__flatcc_reference_ret_val = ret_val;
	}
	__ocall_wrapper_print_buffer___return_value_add(&builder, __flatcc_reference_ret_val);
	__ocall_wrapper_print_buffer_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
void __wrapper_print_value(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	unsigned long val;
	__ocall_wrapper_print_value_table_t function_reference = __ocall_wrapper_print_value_as_root((void *) call_args);
	unsigned long __flatcc_reference_val = __ocall_wrapper_print_value_val(function_reference);
	{
		val = __flatcc_reference_val;
	}
	print_value(val);
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_print_value_start_as_root(&builder);
	__ocall_wrapper_print_value_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
void __wrapper_send_reply(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	void *message;
	unsigned long len;
	__ocall_wrapper_send_reply_table_t function_reference = __ocall_wrapper_send_reply_as_root((void *) call_args);
	unsigned long __flatcc_reference_len = __ocall_wrapper_send_reply_len(function_reference);
	{
		len = __flatcc_reference_len;
	}
	flatbuffers_int8_vec_t __flatcc_reference_message = __ocall_wrapper_send_reply_message(function_reference);
	{
		message = (void *) malloc((len) * sizeof(char));
		for (size_t i1 = 0; i1 < (size_t) (len); ++i1) {
			{
				((char*) message)[i1] = flatbuffers_int8_vec_at(__flatcc_reference_message, i1 + (len) * (0));
			}
		}
	}
	send_reply(message, len);
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_send_reply_start_as_root(&builder);
	__ocall_wrapper_send_reply_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
void __wrapper_send_report(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	void *shared_buffer;
	unsigned long len;
	__ocall_wrapper_send_report_table_t function_reference = __ocall_wrapper_send_report_as_root((void *) call_args);
	unsigned long __flatcc_reference_len = __ocall_wrapper_send_report_len(function_reference);
	{
		len = __flatcc_reference_len;
	}
	flatbuffers_int8_vec_t __flatcc_reference_shared_buffer = __ocall_wrapper_send_report_shared_buffer(function_reference);
	{
		shared_buffer = (void *) malloc((len) * sizeof(char));
		for (size_t i1 = 0; i1 < (size_t) (len); ++i1) {
			{
				((char*) shared_buffer)[i1] = flatbuffers_int8_vec_at(__flatcc_reference_shared_buffer, i1 + (len) * (0));
			}
		}
	}
	send_report(shared_buffer, len);
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_send_report_start_as_root(&builder);
	__ocall_wrapper_send_report_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
void __wrapper_wait_for_client_pubkey(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	__ocall_wrapper_wait_for_client_pubkey_table_t function_reference = __ocall_wrapper_wait_for_client_pubkey_as_root((void *) call_args);
	pubkey *ret_val;
	ret_val = wait_for_client_pubkey();
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_wait_for_client_pubkey_start_as_root(&builder);
	__pointer_pubkey_ref_t __flatcc_reference_ret_val;
	{
		if (ret_val) {
			pubkey_ref_t __keyedge_pointer_data_1;
			{
				pubkey_start(&builder);
				flatbuffers_int8_vec_ref_t __3_data;
				{
					char* __keyedge_array_data_4 = (char*) malloc((1 * (32)) * sizeof(char));
					for (size_t i4 = 0; i4 < (size_t) (32); ++i4) {
						{
							__keyedge_array_data_4[i4 + (32) * (0)] = (*ret_val).data[i4];
						}
					}
					__3_data = flatbuffers_int8_vec_create(&builder, (signed char*)__keyedge_array_data_4, 1 * (32));
					free(__keyedge_array_data_4);
				}
				pubkey_data_add(&builder, __3_data);
				__keyedge_pointer_data_1 = pubkey_end(&builder);
			}
			__flatcc_reference_ret_val = __pointer_pubkey_create(&builder, 0, __keyedge_pointer_data_1);
		} else {
			__pointer_pubkey_start(&builder);
			__pointer_pubkey___is_null_add(&builder, 1);
			__flatcc_reference_ret_val = __pointer_pubkey_end(&builder);
		}
	}
	__ocall_wrapper_wait_for_client_pubkey___return_value_add(&builder, __flatcc_reference_ret_val);
	__ocall_wrapper_wait_for_client_pubkey_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
void __wrapper_wait_for_message(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	__ocall_wrapper_wait_for_message_table_t function_reference = __ocall_wrapper_wait_for_message_as_root((void *) call_args);
	encl_message_t ret_val;
	ret_val = wait_for_message();
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_wait_for_message_start_as_root(&builder);
	encl_message_t_ref_t __flatcc_reference_ret_val;
	{
		encl_message_t_start(&builder);
		unsigned long __1_len;
		{
			__1_len = ret_val.len;
		}
		flatbuffers_int8_vec_ref_t __1_host_ptr;
		{
			char* __keyedge_array_data_2 = (char*) malloc((1 * (ret_val.len)) * sizeof(char));
			for (size_t i2 = 0; i2 < (size_t) (ret_val.len); ++i2) {
				{
					__keyedge_array_data_2[i2 + (ret_val.len) * (0)] = ((char*) ret_val.host_ptr)[i2];
				}
			}
			__1_host_ptr = flatbuffers_int8_vec_create(&builder, (signed char*)__keyedge_array_data_2, 1 * (ret_val.len));
			free(__keyedge_array_data_2);
		}
		encl_message_t_host_ptr_add(&builder, __1_host_ptr);
		encl_message_t_len_add(&builder, __1_len);
		__flatcc_reference_ret_val = encl_message_t_end(&builder);
	}
	__ocall_wrapper_wait_for_message___return_value_add(&builder, __flatcc_reference_ret_val);
	__ocall_wrapper_wait_for_message_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
void register_functions() {
	register_call(__function_print_buffer, __wrapper_print_buffer);
	register_call(__function_print_value, __wrapper_print_value);
	register_call(__function_send_reply, __wrapper_send_reply);
	register_call(__function_send_report, __wrapper_send_report);
	register_call(__function_wait_for_client_pubkey, __wrapper_wait_for_client_pubkey);
	register_call(__function_wait_for_message, __wrapper_wait_for_message);
	return;
}
