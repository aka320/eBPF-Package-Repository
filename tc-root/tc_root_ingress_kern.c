// Copyright Contributors to the L3AF Project.
// SPDX-License-Identifier: (GPL-2.0 OR BSD-2-Clause)

#define KBUILD_MODNAME "foo"

#include <uapi/linux/bpf.h>
#include "tc_root_common.h"

#define bpf_printk(fmt, ...)                                    \
({                                                              \
   char ____fmt[] = fmt;                            \
   bpf_trace_printk(____fmt, sizeof(____fmt),       \
                    ##__VA_ARGS__);                 \
})
                  
struct {
        __uint(type, BPF_MAP_TYPE_PROG_ARRAY);
        __type(key, int);
        __type(value, int);
        __uint(max_entries, ROOT_ARRAY_SIZE);
} tc_ingress_root_array SEC(".maps");
                  
SEC("tc-ingress-root")
int tc_ingress_root(struct __sk_buff *skb) {
    bpf_tail_call(skb, &tc_ingress_root_array, 0);
    return TC_ACT_OK;
}


char _license[] SEC("license") = "Dual BSD/GPL";
