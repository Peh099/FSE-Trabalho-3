#ifndef __LED_RGB_H__
#define __LED_RGB_H__

#define LEDRED 19
#define LEDGREEN 21
#define LEDBLUE 18

void init_wcmcu_h2(void *params);
void set_true_rgb();
void set_false_rgb();

#endif