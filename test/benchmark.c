#define ZPL_IMPLEMENTATION
#define ZPLE_IMPLEMENTATION
#include <zpl.h>
#include <zpl_ent.h>

typedef struct {
    f32 x,y,z;
} ZPLE_COMP_DECLARE(transform);

void transform_print_cb(zple_id_t handle, transform_t *tran) {
    zpl_printf("%f, %f, %f\n", tran->x, tran->y, tran->z);
}

// NOTE(ZaKlaus): Put this EXACTLY to one source file!
ZPLE_COMP_DEFINE(transform);

int main(void) {

    
    // NOTE(ZaKlaus): Initialize our entity pool
    zple_pool pool = {0};
    zple_init(&pool, zpl_heap_allocator(), 4000000);

    // NOTE(ZaKlaus): Initialize our component pool
    // WARN(ZaKlaus): Component pool of type X can be used EXACTLY by ONE entity pool EXCLUSIVELY!!!
    transform_pool tranpool = {0};
    transform_init(&tranpool, &pool, zpl_heap_allocator());
    isize u = zpl_utc_time_now();
    // NOTE(ZaKlaus): Generate some entities.
    for (isize i = 0; i < 4000000; ++i) {
        zple_id_t h = zple_create(&pool);
        transform_attach(&tranpool, h, (transform_t){i, i*2, i*i});
    }
    isize a = (zpl_utc_time_now()-u);
    zpl_printf("Took: %f ms", a/1000.0f);

    // NOTE(ZaKlaus): Release our resources
    transform_free(&tranpool);
    zple_free(&pool);

    return 0;
}
