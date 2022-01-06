#ifndef PUSH_SWAP_DISTANCE_H
#define PUSH_SWAP_DISTANCE_H

void find_best_actions(int *min_actions, t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);
int find_actions(int *one_actions);
int min_dist(int a, int b, int *d);
int f(int rarb);

#endif //PUSH_SWAP_DISTANCE_H
