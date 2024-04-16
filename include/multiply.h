struct Matrix naive_multiply_square(struct Matrix A, struct Matrix B);
struct Matrix Winograd_multiply_square(struct Matrix A, struct Matrix B);
struct Matrix mat_add(struct Matrix A, struct Matrix B);
struct Matrix mat_neg(struct Matrix mat);
struct Matrix get_matrix_block(int x0, int x1, int y0, int y1, struct Matrix mat);
struct Matrix padding(struct Matrix mat);