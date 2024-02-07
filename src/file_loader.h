#ifndef FILE_LOADER_H
#define FILE_LOADER_H
#endif

//void load_file_in_ram(struct ram *memory, uint64_t addr, uint8_t *name);
//void load_files(struct ram *memory, struct file *first_file);
void load_bootfile_in_ram(struct ram *mempry, struct opt *options);
