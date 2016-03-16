#include <iostream>


//
// Описание узла дерева
//
struct node
{
	long data;
	struct node *left;
	struct node *right;
};

node * constructSubTree( long pre[], long* preIndex, long key,
							   long min, long max, long size );

struct node *constructTree (int pre[], int size, long min, long max);

// Создаем узел
struct node * newNode (long data)
{
	struct node * temp =  new struct node;
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

// Сборка дерева
struct node * constructSubTree( long pre[], long* preIndex, long key,
							   long min, long max, long size )
{
	// Осмотр закончен - дальше погружаться некуда, это лист
	if( *preIndex >= size )
		return NULL;
	
	struct node* root = NULL;
	
	// Если текущий элемент из pre[] принадлежит заданному диапазону,
	// то он является компонентом текщего поддерева
	if( key >= min && key <= max ) 
	{
		// создаем новый узел для корня этого поддерева и увеличиваем *preIndex
		root = newNode ( key );
		*preIndex = *preIndex + 1;
		
		if (*preIndex < size) 
		{
			// Начинаем cобирать поддерево для этого корня
			// все узлы от min до key - налево, все прочие - направо
			// ну а первый из диапазлна min.key - это корень нашего левого поддерва
			root->left = constructSubTree( pre, preIndex, pre[*preIndex],
										   min, key, size );
			
			// Первый из тех, что пошли направо тоже становится корешком поддерева
			// но уже привязанного к текущему корню справа
			root->right = constructSubTree( pre, preIndex, pre[*preIndex],
											key, max, size );
		}
	}
	else if (key > max)
	{
		return NULL;
	}
	else
		return NULL;
	// Возвращаем указатель на корень сформированного дерева
	return root;
}


// Вывод субдерева в обратном порядке обхода
void postOrderPrint(struct node* root) 
{
    if (root) {
        postOrderPrint(root->left);
        postOrderPrint(root->right);
        std::cout<< root->data << " ";
    }
	else
		return;
}
 

/////

int main(int argc, const char * argv[]) {

	long treeSize;
	
#ifndef TEST_RUN
	std::cin >> treeSize;
#endif
	
	long *preorderTree = new long[treeSize];
	
#ifndef  TEST_RUN
	for (long i = 0; i < treeSize; i++) {
		std::cin >> preorderTree[i];
	}
#endif
	
	long minNode = 2147483647;
	long maxNode = -2147483647;
	for (long i = 0; i < treeSize; i++) {
		minNode = (minNode > preorderTree[i] ? preorderTree[i] : minNode);
		maxNode = (maxNode < preorderTree[i] ? preorderTree[i] : maxNode);
	}
	
	// Собираем дерево
	long preIndex = 0;
	struct node * tree = constructSubTree(preorderTree, &preIndex, preorderTree[0], minNode, maxNode, treeSize);
	
	
	postOrderPrint(tree);
}
