
/* timer.c */
int            set_pit_counter(int, unsigned char, unsigned char);
void           init_pit(void);

/* keyboard.c */
unsigned char read_keyboard_control_status(void);
int           write_keyboard_control_command(unsigned char command);
unsigned char read_keyboard_encoder_buffer(void);
int           write_keyboard_encoder_command(unsigned char command);
