#include "../../includes/parsing.h"

// nothing but we just making sure path is valid
bool valid_path_input(char *path) {
    char *dot = strrchr(path, '.');
    if (dot && strcmp("cub", dot + 1) == 0) return true;
    return false;
}

// buidling list of lines to get the file and close the fd ;
t_lstfile *r_file(int fd) {
    t_lstfile *(lst);
    lst = malloc(sizeof(t_lstfile));
    if (!lst) return NULL;
    t_file *head = NULL;
    t_file *current = NULL;
    char *tmp;
    while ((tmp = get_next_line(fd))) {
        t_file *new_node = malloc(sizeof(t_file));
        if (!new_node) return NULL;
        new_node->line = tmp;
        new_node->next = NULL;
        if (!head) {
            head = new_node;
            current = new_node;
        } else {
            current->next = new_node;
            current = new_node;
        }
    }
    lst->head = head;
    return lst;
}

void print_cfile(t_lstfile *lst) {
    t_file *file = lst->head;
    while (file) {
        printf("%s", file->line);
        file = file->next;
    }
}
bool is_txt(char *path) {
    return (!strncmp(path, "NO", 2) || !strncmp(path, "WE", 2) || !strncmp(path, "EA", 2) ||
            !strncmp(path, "SO", 2));
}

bool valid_path_xpm(char *path) {
    char *xpm = strrchr(path, '.');
    if (strncmp(xpm, ".xpm", 4) == 0) return true;
    return false;
}
bool dup_dir(t_textures *t, char *dir) {
    if ((t->ea && strncmp(dir, "EA", 2) == 0) || (t->no && strncmp(dir, "NO", 2) == 0) ||
        (t->so && strncmp(dir, "SO", 2) == 0) || (t->we && strncmp(dir, "WE", 2) == 0))
        return true;
    return false;
}

bool get_txt_path(t_textures **tx, char *txt) {
    t_textures *x = *tx;
    char *path = strchr(txt, '.');
    while (isspace((unsigned char)*path)) path++;
    int size = strlen(path) - 1;
    while (size >= 0 && isspace((unsigned char)path[size])) {
        path[size] = '\0';
        size--;
    }
    if (dup_dir(x, txt)) {
        write(2, path, 2);
        return false;
    }
    if (!valid_path_xpm(path)) {
        printf("not valid path xpm!\n");
        return false;
    }
    if (strncmp(txt, "NO", 2) == 0)
        x->no = ft_strdup(path);
    else if (strncmp(txt, "WE", 2) == 0)
        x->we = ft_strdup(path);
    else if (strncmp(txt, "SO", 2) == 0)
        x->so = ft_strdup(path);
    else if (strncmp(txt, "EA", 2) == 0)
        x->ea = ft_strdup(path);
    else
        return false;
    return true;
}

bool all_txt_set(t_textures *t) { return (t->ea && t->no && t->so && t->we); }
void free_lstfile(t_lstfile *lst) {
    t_file *tmp;
    tmp = lst->head;
    if (lst->txts) {
        t_textures *txts = lst->txts;
        free(txts->ea);
        free(txts->we);
        free(txts->no);
        free(txts->so);
        free(txts);
    }
    while (tmp) {
        t_file *next = NULL;
        next = tmp->next;
        free(tmp->line);
        free(tmp);
        tmp = next;
    }
    free(lst);
}
bool texture_exist(t_textures *t) {
    int fd[4] = {
        open(t->ea, O_RDONLY), open(t->so, O_RDONLY), open(t->no, O_RDONLY), open(t->we, O_RDONLY)};
    if (fd[0] < 0 || fd[1] < 0 || fd[2] < 0 || fd[3] < 0) {
        int i = 0;
        while (i < 4) {
            if (fd[i] >= 0) close(fd[i]);
            i++;
        }
        return false;
    }
    return true;
}

void free_array(char **m)
{
    int i = 0;
    while (m[i]) free(m[i++]);
    free(m);
}

bool get_path_txts(t_lstfile **lst) {
    t_lstfile *l = *lst;
    t_textures *t;
    t = malloc(sizeof(t_textures));
    t_file *tmp;

    t->ea = NULL;
    t->no = NULL;
    t->so = NULL;
    t->we = NULL;
    tmp = l->head;
    while (tmp) {
        if (is_txt(tmp->line)) {
            if (!get_txt_path(&t, tmp->line)) return false;
            if (all_txt_set(t)) break;
        }
        tmp = tmp->next;
    }
    if (!all_txt_set(t)) return false;
    l->txts = t;
    if (!texture_exist(t)) {
        printf("a texture file not exist\n");
        return false;
    }
    return true;
}

bool valid_clrs(char *str, int p) {
    int i = 0;
    while (ft_isdigit(str[i])) i++;

    if (str[i] && str[i] != '\n') return false;
    if (p != 2 && str[i] == '\n') return false;
    return true;
}

int get_color(char *line)
{
    char **color;
    line++;
    while (isspace(*line) && !ft_isdigit(*line)) line++;
    color = ft_split(line, ',');
    if (color[3] != NULL) return -1;

    // make sure that all the strings containt the colors rgb are clean and contain only numbers and
    // , and \n at the end
    if (!valid_clrs(color[1], 1) || !valid_clrs(color[0], 0) || !valid_clrs(color[2], 2)) return -1;

    int r = ft_atoi(color[0]);
    int g = ft_atoi(color[1]);
    int b = ft_atoi(color[2]);
    // bit shifting

    free_array(color);
    if (r > 255 || g > 255 || b > 255) return -1;
    int fc;
    fc = (r << 16) | (g << 8) | b;
    return fc;
}

bool get_cf(t_lstfile **lst)
{
  t_lstfile *l = *lst;
  t_file *node = l->head;
  int flag = 0;

  while (node)
  {
    if (strncmp(node->line, "F", 1) == 0)
    {
      l->floor = get_color(node->line);
      if (l->floor == -1) break;
      flag++;
    }
    else if(strncmp(node->line , "C" , 1) == 0)
    {
      l->ceiling = get_color(node->line);
      if (l->ceiling == -1) break;
      flag++;
    }
    if(flag == 2)
      break;
    node = node->next;
  }
  if (flag != 2) return false;
  return true;
}

bool valid_file(t_lstfile *lst)
{
  if(!get_path_txts(&lst)) // map , color , textures .
    return false;
  if (!get_cf(&lst)) return false;
  return true;
}
