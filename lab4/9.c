#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct
{
	int size;
	struct t_tree **node;
}vector;

typedef struct t_tree
{
	char name;
	struct t_tree *parent;
	vector child;
}s_tree;

s_tree *create_new_el(s_tree *node)
{
	s_tree *new;

	new = (s_tree*)malloc(sizeof(s_tree));
	new->parent = node;
	new->child.size = 0;
	return (new);
}

void push(char *str, s_tree **tree)
{
	s_tree *shift = *tree;
	int level = 0;
	while (*str)
	{
		if (isalpha(*str))
		{
			if (!shift)
			{
				shift = create_new_el(NULL);
				shift->name = *str;
				str++;
				continue;
			}
			shift->child.size++;
			if (shift->child.size == 1)
				shift->child.node = malloc(sizeof(s_tree));
			else 
				shift->child.node = realloc(shift->child.node, sizeof(s_tree) * shift->child.size);
			shift->child.node[shift->child.size - 1] = create_new_el(shift);
			shift->child.node[shift->child.size - 1]->name = *str;
			str++;
			continue ;
		}
		if (*str == '(')
		{
			if (level)
				shift = shift->child.node[shift->child.size - 1];
			level++;
		}
		if (*str == ')')
		{
			level--;
			if (level)
				shift = shift->parent;
		}
		str++;
	}
	*tree = shift;
}

void print_tree(s_tree *tree, int level)
{
	for (int i = 0; i < level; i++)
	{
		printf("-");
	}
	printf("%c\n", tree->name);
	for (int i = 0; i < tree->child.size; i++)
	{
		print_tree(tree->child.node[i], level + 1);
	}
}

void del_all(s_tree *tree)
{
	for (int i = 0; i < tree->child.size; i++)
	{
		del_all(tree->child.node[i]);
		free(tree->child.node[i]);
	}
	free(tree->child.node);
}

int main()
{
	s_tree *tree = NULL;

	push("A (B (E (G, T, R (W, Z)), F (L, M)), C)", &tree);
	print_tree(tree, 0);
	del_all(tree);
	free(tree);
}