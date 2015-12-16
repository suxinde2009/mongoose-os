#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "smartjs/src/sys_config.h"
#include "v7/v7.h"

/* Read-only firmware setting */
struct ro_var {
  struct ro_var *next;
  const char *name;
  const char **ptr;
};
extern struct ro_var *g_ro_vars;

#define REGISTER_RO_VAR(_name, _ptr) \
  do {                               \
    static struct ro_var v;          \
    v.name = (#_name);               \
    v.ptr = (_ptr);                  \
    v.next = g_ro_vars;              \
    g_ro_vars = &v;                  \
  } while (0)

/* Common init provides this API */
int init_device(struct v7 *);

/* Common init calls this API: must be implemented by each platform */
int device_init_platform(struct sys_config *);
void device_reboot(void);
void device_get_mac_address(uint8_t mac[6]);

#endif