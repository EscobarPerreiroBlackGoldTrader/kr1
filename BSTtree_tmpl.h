#ifndef BSTTREE_TMPL_H
#define BSTTREE_TMPL_H

#include <QStack> //необходим для итеративных алгоритмов обхода BST-дерева
#include <QTextEdit> //необходим для вывода дерева на экран

// в фигурных скобках отмечены ошибки {1} - 1-я {2} - вторая
// BST-дерево - дерево бинарного поиска
//=================================================================================================================
template <typename Key,typename Data>
         class BSTtree
{
public:

             //-_-_-_-_-_-_-_- ВСТРОЕННЫЙ УЗЕЛ -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
             class node
             {
             public:
                 node():left(0),right(0) {} //конструктор без параметров

                 node(Data newdata,Key newkey):left(0),right(0){//конструктор корня дерева
                     itdata = newdata;
                     itkey = newkey;
                 }
                 node(Data newdata, Key newkey,node *newleft,node *newright){//конструктор встроенного узла дерева
                     itdata = newdata;
                     itkey = newkey;
                     left = newleft;
                     right = newright;
                 }
                 node(const node& mainnode){// конструктор-копировщик (копирует только значения!!!)
                     itdata = mainnode.itdata;
                     itkey = mainnode.itkey;
                     left = mainnode.left;
                     right = mainnode.right;
                 }


//                ~node()
//                 { // проверить работоспособность
//                     if(left){
//                        delete left; //удаление левой ветки
//                        left = NULL; // обязательно занулить!!!
//                     }

//                     if(right){
//                        delete right; //удаление правой ветки
//                        right = NULL; // обязательно занулить!!!
//                     }
//                 }

                 //--------- дааные открыты для упрощения доступа к ним ---------------
                 Data itdata; //данные узла
                 Key itkey; //ключ узла
                 node *left; // указатель на левое поддерево
                 node *right; // указатель на правое поддерево
             };
             //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-




         BSTtree():root(0),treesize(0) {} //конструктор без параметров

         BSTtree(node *newroot):root(0),treesize(0){//конструктор с созданием корневого узла
             //++treesize; // увеличиваем счётчик узлов на один. неправильно!!!

               treesize = GetTreeSizeWalking(newroot);

               QStack<node*> stkF; //стек указателей на узлы копируемого дерева
               QStack<node*> stkS; // стек указателей на узлы дерева-приёмника
               stkF.push(newroot);

               node * tmpF = NULL;
               node * tmpS = NULL;
               node* tmproot;

               if(!newroot){ // если исходное дерево пусто
                   //ClearTree(root); // очищаем конечное
                   treesize = 0;
                   //return *this;//выходим
               }else{// если нет
                   //ClearTree(root); // всё равно очищаем конечное так как данные в нём нам не нужны
                   stkS.push(root);

                   while(!stkF.isEmpty() && !stkS.isEmpty()){

                       tmpF = stkF.pop();
                       tmpS = stkS.pop();

                       //----- операция над узлом --------
                          if(tmpS == NULL){
                              tmpS = new node(tmpF->itdata,tmpF->itkey);
                              tmproot = tmpS;

                              if(tmpF->left != NULL)tmpS->left = new node(tmpF->left->itdata,tmpF->left->itkey);
                              if(tmpF->right != NULL)tmpS->right = new node(tmpF->right->itdata,tmpF->right->itkey);

                          }else{

                              if(tmpF->left != NULL)tmpS->left = new node(tmpF->left->itdata,tmpF->left->itkey);
                              if(tmpF->right != NULL)tmpS->right = new node(tmpF->right->itdata,tmpF->right->itkey);


                          }
                       //---------------------------------

                       if(tmpF->right != NULL){ // если указатель на правое поддерево не пуст
                           stkF.push(tmpF->right);
                           stkS.push(tmpS->right);
                       }

                       if(tmpF->left != NULL){// если указатель на левое поддерево не пуст
                           stkF.push(tmpF->left);// запихиваем его в стек
                           stkS.push(tmpS->left);
                       }
                   }

                   //treesize = rhs.treesize; // копируем количество узлов исходного дерева
                   this->root = tmproot;
                   //return *this;
               }

         }

         BSTtree(const BSTtree &rhs){// конструктор-копировщик

             QStack<node*> stkF; //стек указателей на узлы копируемого дерева
             QStack<node*> stkS; // стек указателей на узлы дерева-приёмника
             stkF.push(rhs.root);

             node * tmpF = NULL;
             node * tmpS = NULL;

             node* tmproot = this->root;
             //this->root = NULL;

             if(!rhs.root){ // если исходное дерево пусто
                 //ClearTree(root); // очищаем конечное
                 root = rhs.root;
                 treesize = 0;
                 return;//выходим
             }else{// если нет
                 //ClearTree(root); // всё равно очищаем конечное так как данные в нём нам не нужны
                 stkS.push(root);

                 while(!stkF.isEmpty() && !stkS.isEmpty()){

                     tmpF = stkF.pop();
                     tmpS = stkS.pop();

                     //----- операция над узлом --------
                        if(tmpS == tmproot){
                             tmpS = new node(tmpF->itdata,tmpF->itkey);
                             tmproot = tmpS; // запоминаем корень дерева
//                            tmpS->itdata = tmpF->itdata;
//                            tmpS->itkey = tmpF->itkey;

                            if(tmpF->left != NULL)tmpS->left = new node(tmpF->left->itdata,tmpF->left->itkey);
                            if(tmpF->right != NULL)tmpS->right = new node(tmpF->right->itdata,tmpF->right->itkey);

                        }else{

                            if(tmpF->left != NULL)tmpS->left = new node(tmpF->left->itdata,tmpF->left->itkey);
                            if(tmpF->right != NULL)tmpS->right = new node(tmpF->right->itdata,tmpF->right->itkey);


                        }
                     //---------------------------------

                     if(tmpF->right != NULL){ // если указатель на правое поддерево не пуст
                         stkF.push(tmpF->right);
                         stkS.push(tmpS->right);
                     }

                     if(tmpF->left != NULL){// если указатель на левое поддерево не пуст
                         stkF.push(tmpF->left);// запихиваем его в стек
                         stkS.push(tmpS->left);
                     }
                 }

                 treesize = rhs.treesize; // копируем количество узлов исходного дерева
                 root = tmproot;
             }

         }

         BSTtree& operator=(const BSTtree& rhs){ // перегрузка оператора присваивания

             QStack<node*> stkF; //стек указателей на узлы копируемого дерева
             QStack<node*> stkS; // стек указателей на узлы дерева-приёмника
             stkF.push(rhs.root);

             node * tmpF = NULL;
             node * tmpS = NULL;
             node* tmproot;

             if(!rhs.root){ // если исходное дерево пусто
                 ClearTree(root); // очищаем конечное
                 treesize = 0;
                 return *this;//выходим
             }else{// если нет
                 ClearTree(root); // всё равно очищаем конечное так как данные в нём нам не нужны
                 stkS.push(root);

                 while(!stkF.isEmpty() && !stkS.isEmpty()){

                     tmpF = stkF.pop();
                     tmpS = stkS.pop();

                     //----- операция над узлом --------
                        if(tmpS == NULL){
                            tmpS = new node(tmpF->itdata,tmpF->itkey);
                            tmproot = tmpS;

                            if(tmpF->left != NULL)tmpS->left = new node(tmpF->left->itdata,tmpF->left->itkey);
                            if(tmpF->right != NULL)tmpS->right = new node(tmpF->right->itdata,tmpF->right->itkey);

                        }else{

                            if(tmpF->left != NULL)tmpS->left = new node(tmpF->left->itdata,tmpF->left->itkey);
                            if(tmpF->right != NULL)tmpS->right = new node(tmpF->right->itdata,tmpF->right->itkey);


                        }
                     //---------------------------------

                     if(tmpF->right != NULL){ // если указатель на правое поддерево не пуст
                         stkF.push(tmpF->right);
                         stkS.push(tmpS->right);
                     }

                     if(tmpF->left != NULL){// если указатель на левое поддерево не пуст
                         stkF.push(tmpF->left);// запихиваем его в стек
                         stkS.push(tmpS->left);
                     }
                 }

                 treesize = rhs.treesize; // копируем количество узлов исходного дерева
                 this->root = tmproot;
                 return *this;
             }

         }

         ~BSTtree(); // деструктор

//         Интерфейс АТД «BST – дерево» включает  следующие операции:
//         •	опрос размера дерева (количества узлов),
//         •	очистка дерева (удаление всех узлов),
//         •	проверка дерева на пустоту,
//         •	поиск данных с заданным ключом,
//         •	включение в дерево нового узла с заданным ключом и данными,
//         •	удаление из дерева узла с заданным ключом,
//         •	обход узлов в дереве по схеме, заданной в варианте задания, и вывод ключей в порядке обхода,
//         •	дополнительная операция, заданная в варианте задания (объединение двух BST-деревьев).

        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
         node*& getRoot(){return root;} // возвращает ссылку на указатель на корень дерева
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
         node* BST_root_insert(node *&rootA,Key key,Data data,bool& inserted){ // вставка нового узла в корень дерева
             bool ins;

             if(rootA == NULL){// !!!сама вставка!!! найдено свободное место
                 inserted = true;
                 ++treesize;
                 return new node(data,key);
             }

             if(key == rootA->itkey){
                 inserted = false;
                 return rootA;
             }

             if(key < rootA->itkey){//---
                 rootA->left = BST_root_insert(rootA->left,key,data,ins);
                 inserted = ins;

                 if(ins){
                     return R(rootA);
                 }else{
                     return rootA;
                 }
             }else{//---------------------

                 rootA->right = BST_root_insert(rootA->right,key,data,ins);
                 inserted = ins;

                 if(ins){
                     return L(rootA);
                 }else{
                     return rootA;
                 }
             }//---

         }
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
         //node* Root_insert(node* a,node* b);
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        //********************************************************
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
         int GetTreeSize(); //опрос размера дерева (количества узлов)
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
         int GetTreeSizeWalking(node* troot);
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
         void ClearTree(node *&n){ //очистка дерева (удаление всех узлов). принять указатель как ссылку!!!!

             if(n == NULL)return;

                if(n->left != NULL)ClearTree(n->left);
                if(n->right != NULL)ClearTree(n->right);
                delete n;
                n = NULL; // ОБЯЗАТЕЛЬНО !!!
                --treesize;
                return;
         }
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
         bool isEmtyTree(){ //проверка дерева на пустоту {1}
             if(root)return false;
             return true;
         }
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        Data GetData(Key key, bool &isPresent); //поиск данных с заданным ключом
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        bool addNode(Data data,Key key); //включение в дерево нового узла с заданным ключом и данными
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        bool delNode(Key key); // удаление из дерева узла с заданным ключом,
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        Key** GetWalking();// возвращает массив указателей на ключи
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        void Join(BSTtree<Key, Data> tree);
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        void ShowTree(QTextEdit *&pte, node *&rootA, int level = 0);
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

private:
        node *root; //корень дерева
        int treesize; // размер дерева

        //------
        node*& BST_Join(node *&a,node *&b){// a - дерево которое необходимо
                                           // вставить в дерево b, при этом дерево a разрушается,
                                           // поэтому необходимо передавать дерево а как параметр
                                           // в функциях вызывающих данную.



           bool instd;

           if(a == NULL)return b;// вставлять нечего,
                                 // возвращаем указатель на дерево
                                 // в которое планировалась вставка

           if(b == NULL){   // вставлять некуда, возвращаем указатель
               //вернуть копию а на куче !!! return copytree(a);
               // и промериить её
               // treesize += a.gettreesize()
               //++treesize;  // на вставляемое, тоесть вставляем дерево в

               BSTtree<Key,Data> *tmpTree = new BSTtree<Key,Data>;

               //(*tmpTree) = (*a);
               tmpTree->operator =(a);

               treesize += tmpTree->GetTreeSizeWalking(tmpTree->getRoot());

               return tmpTree->getRoot();    // пустой указатель конечного дерева
           }

           node* left = a->left;
           node* right = a->right;

           a->left = NULL;
           a->right = NULL;

           if(a->itkey == b->itkey){
               //delNode(a->itkey);//?????
               delete a;//проверить правильность удаления узла!!!
               a = NULL;// декремнт ненужен так как дерево а идёт на "разбор"
           }else{
               b = BST_root_insert(b,a->itkey,a->itdata,instd);
           }

           b->left = BST_Join(left,b->left);
           b->right = BST_Join(right,b->right);
           return b;
       }
       //------
       node* L(node *&rootA){// вытолкнуть rootA влево

            if(rootA == NULL){
                //return NULL;
                node* pusto = NULL;
                return pusto;
            }else{
                node *x = NULL; //new node;// утечка памяти, исправить!!!

                x = rootA->right;
                rootA->right = x->left;
                x->left = rootA;
                return x;
            }
       }
       //------
       node* R(node *&rootA){// вытолкнуть rootA вправо

           if(rootA == NULL){
               //return NULL;
               node* pusto = NULL;
               return pusto;
           }else{
               node *x = NULL; //new node;// утечка памяти, исправить!!!

               x = rootA->left;
               rootA->left = x->right;
               x->right = rootA;
               return x;
           }

       }
       //------
//       bool Delete_node_tree(node* rootA, Key key){}
};
//=================================================================================================================
/*
template <typename Key,typename Data>
BSTtree<Key,Data>::BSTtree(const BSTtree<Key,Data> &rhs){// конструктор-копировщик

    QStack<node*> stkF; //стек указателей на узлы копируемого дерева
    QStack<node*> stkS; // стек указателей на узлы дерева-приёмника
    stkF.push(rhs.root);
    stkS.push(root);
    node * tmpF = NULL;
    node * tmpS = NULL;

    if(!rhs.root){ // если исходное дерево пусто
        ClearTree(root); // очищаем конечное
        treesize = 0;
        return;//выходим
    }else{// если нет
        ClearTree(root); // всё равно очищаем конечное так как данные в нём нам не нужны

        while(!stkF.isEmpty() && !stkS.isEmpty()){

            tmpF = stkF.pop();
            tmpS = stkS.pop();

            //----- операция над узлом --------
               if(tmpS == NULL){
                    tmpS = new node(tmpF->itdata,tmpF->itkey);

                   if(tmpF->left != NULL)tmpS->left = new node(tmpF->left->itdata,tmpF->left->itkey);
                   if(tmpF->right != NULL)tmpS->right = new node(tmpF->right->itdata,tmpF->right->itkey);

               }else{

                   if(tmpF->left != NULL)tmpS->left = new node(tmpF->left->itdata,tmpF->left->itkey);
                   if(tmpF->right != NULL)tmpS->right = new node(tmpF->right->itdata,tmpF->right->itkey);


               }
            //---------------------------------

            if(tmpF->right != NULL){ // если указатель на правое поддерево не пуст
                stkF.push(tmpF->right);
                stkS.push(tmpS->right);
            }

            if(tmpF->left != NULL){// если указатель на левое поддерево не пуст
                stkF.push(tmpF->left);// запихиваем его в стек
                stkS.push(tmpS->left);
            }
        }

        treesize = rhs.treesize; // копируем количество узлов исходного дерева

    }

}
*/
//=================================================================================================================
template <typename Key,typename Data>
 BSTtree<Key,Data>::~BSTtree(){
    if(!root)return; // если корнь пуст - выходим

    // проверить выриант на утечки памяти!!!
    // код должен по цепчке вызвать деструкторы во всех node
    //delete root;//???????(проверить)
    ClearTree(root);
    //root = NULL;
 }
//=================================================================================================================
template <typename Key,typename Data>
 int BSTtree<Key,Data>::GetTreeSize(){
     return treesize;
 }

//=================================================================================================================
template <typename Key,typename Data>
 int BSTtree<Key,Data>::GetTreeSizeWalking(node *troot){

     int ts = 0;

     QStack<node*> stk;

     stk.push(troot);

     node * tmp = NULL;

     if(!troot){ // если исходное дерево пусто
         return ts;//выходим
     }else{// если нет

         while(!stk.isEmpty()){

             tmp = stk.pop();


             //----- операция над узлом --------
                ++ts;
             //---------------------------------

             if(tmp->right != NULL){ // если указатель на правое поддерево не пуст
                 stk.push(tmp->right);

             }

             if(tmp->left != NULL){// если указатель на левое поддерево не пуст
                 stk.push(tmp->left);// запихиваем его в стек

             }
         }//end of while
     }//end of else
     return ts;
 }

//=================================================================================================================
template <typename Key,typename Data> // ???найти возможность исправить корявость???
Data BSTtree<Key, Data>::GetData(Key key, bool &isPresent){

     if(!root){// если дерево пустое
        isPresent = false; // если отсутствует искомый элемент
        Data d;
        return d; //????? пустое значение зависит от конкретного типа данных ?????
                  // необходима проверка типа данных для более точного алгоритма
     }

    // Итеративный алгоритм обхода BST-дерева
    // и поиск нужного ключа

     QStack<node*> stk; //стек указателей на узлы

     stk.push(root);
     node * tmp = 0;

     while(!stk.isEmpty()){

         tmp = stk.pop();

         //----- операция над узлом --------
            if(tmp->itkey == key){ // если ключ текущего узла равен искомому
                isPresent = true; // если отсутствует искомый элемент
                return tmp->itdata; // возвращаем искомые данные
            }
         //---------------------------------

         if(tmp->right != NULL){ // если указатель на правое поддерево не пуст
             stk.push(tmp->right);
         }

         if(tmp->left != NULL){// если указатель на левое поддерево не пуст
             stk.push(tmp->left);// запихиваем его в стек
         }
     }

    isPresent = false; // если отсутствует искомый элемент
 }

//=================================================================================================================
template <typename Key,typename Data>
bool BSTtree<Key, Data>::addNode(Data data, Key key){

    if(root == NULL){// если нет ни одного узла в дереве
        root = new node(data,key);
        ++treesize;
        return true;// выход с успехом
    }

    node *t = root;
    node *pred = NULL;

    while(t != NULL){ // поиск свободного места под узел

        pred = t;

        if(key == t->itkey)return false; // выход с ошибкой, такой ключ уже есть

        if(key < t->itkey){
            t = t->left;
        }else{
            t = t->right;
        }
    }// нашли пустой указатель

    if(key < pred->itkey){ // подгонка по месту
        pred->left = new node(data,key); // если ключ меньше ключа верхнего узла - запихиваем в левую часть поддерева
        ++treesize;
    }else{
        pred->right = new node(data,key);// если больше - в правую
        ++treesize;
    }

    return true; // вставка прошла удачно
}

//=================================================================================================================
template <typename Key,typename Data>
bool BSTtree<Key, Data>::delNode(Key key){

    node *t = root, *pred = NULL; //временный указатель , указатель на предыдущий
    node *t0 = NULL, *x = NULL; //временные указатели

    while(t != NULL && t->itkey != key){//пока t не пустой и ключ в t не равен ключу на удаление
        pred = t;                       // запоминаем t как предыдущий

        //ищем по ключу узел на удаление
        if(key < t->itkey){ //если ключ в t больше искомого ключа
            t = t->left;    //уходим искать в левое поддерево
        }else{              // если нет
            t = t->right;   // ищем в правом поддереве
        }

    }// end of while Ищем пока не кончится дерево

    if(t == NULL)return false; // искомый ключ не найден - выходим

    //нашли узел с ключом, проверяем положение узла в дереве
    if(t->left != NULL && t->right != NULL){ // если указатели на правое и левое поддеревья не пусты
        t0 = t; //запоминаем начало
        pred = t;//запоминаем t как предыдущий
        t = t->right; // уходим в правое поддерево

        while(t->left != NULL){ //
            pred = t;
            t = t->left;
        }
        x = t->right;
    }else{
        t0 = NULL;

        if(t->left == NULL && t->right == NULL) x = NULL;

        if(t->left == NULL) x = t->right;

        if(t->right == NULL) x = t->left;
    }

    if(pred == NULL){
        root = x;
    }else{
        if(t->itkey < pred->itkey){
            pred->left = x;
        }else{
            pred->right = x;
        }
    }

    if(t0 != NULL){
        t0->itkey = t->itkey;
        t0->itdata = t->itdata;
    }

    delete t;
    --treesize;
    return true;

}
//=================================================================================================================
template <typename Key,typename Data>
Key** BSTtree<Key, Data>::GetWalking(){

    if(!root)return NULL;//??? проверить на вылет

    // Итеративный алгоритм обхода BST-дерева, t-L-R


     QStack<node*> stk; //стек указателей на узлы

     stk.push(root);
     node * tmp = 0;
     const int sz(treesize); // !!!инициализация переменой sz для создания массива в динамической памяти!!!
     Key **kArr = new Key*[sz]; //массив указателей в динамической памяти на ключи


     for(int i=0;!stk.isEmpty();++i){
         tmp = stk.pop();

         //----- операция над узлом --------
          kArr[i] = &(tmp->itkey); //собираем указатели в массив
         //---------------------------------

         if(tmp->right != NULL){ // если указатель на правое поддерево не пуст
             stk.push(tmp->right);
         }

         if(tmp->left != NULL){// если указатель на левое поддерево не пуст
             stk.push(tmp->left);// запихиваем его в стек
         }
     }

     return kArr; // возвращаем указвтель на массив указателей на ключи
}

//=================================================================================================================
/*
//template <typename Key,typename Data>
//node* BSTtree<Key, Data>::BST_Join(node* a,node *b){


//    bool instd;

//    if(a == NULL)return b;
//    if(b == NULL)return a;

//    node* left = a->left;
//    node* right = a->right;

//    a->left = NULL;
//    a->right = NULL;

//    if(a->itkey == b->itkey){
//        delNode(a->itkey);
//    }else{
//        b = BST_root_insert(b,a->itkey,a->itdata,instd);
//    }

//    b->left = BST_Join(left,b->left);
//    b->right = BST_Join(right,b->right);
//    return b;
//}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
template <typename Key,typename Data>
void BSTtree<Key, Data>::Join(BSTtree<Key, Data> tree){

    //root = BST_Join(root,tree.getRoot());

    root = BST_Join(tree.getRoot(),root); // в корень конечного будет вставлено обьединённое дерево
    //++treesize;

}
//=================================================================================================================
template <typename Key,typename Data>
void BSTtree<Key, Data>::ShowTree(QTextEdit *&pte,node *&rootA,int level){
   /*
    if(rootA == NULL)return;

    ShowTree(pte,rootA->right,level+1);

    for(int i = 0; i < level; ++i){

        pte->insertPlainText(" ");
    }
        pte->insertPlainText(QString::number(rootA->itkey));
        pte->insertPlainText("\n");



    ShowTree(pte,rootA->left,level+1);
    */

    if(rootA->right)ShowTree(pte,rootA->right,level+1);

    for(int i = 0; i < (3*level); ++i){

        pte->insertPlainText("   ");
    }

    pte->insertPlainText(QString::number(rootA->itkey)+ "\n\n");


    if(rootA->left)ShowTree(pte,rootA->left,level+1);
}

//=================================================================================================================
/*
//template <typename Key,typename Data>
//node* BSTtree<Key,Data>::Root_insert(node *a, node *b){

//}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//template <typename Key,typename Data>
//node* BSTtree<Key,Data>::BST_root_insert(node *rootA, Key key, Data data, bool &inserted){
//    bool ins;

//    if(rootA == NULL){
//        inserted = true;
//        return new node(key,data);
//    }

//    if(key == rootA->itkey){
//        inserted = false;
//        return rootA;
//    }

//    if(key < rootA->itkey){//---
//        rootA->left = BST_root_insert(rootA->left,key,data,ins);
//        inserted = ins;

//        if(ins){
//            return R(rootA);
//        }else{
//            return rootA;
//        }
//    }else{//---------------------

//        root->right = BST_root_insert(rootA->right,key,data,ins);
//        inserted = ins;

//        if(ins){
//            return L(rootA);
//        }else{
//            return rootA;
//        }
//    }//---

//}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//template <typename Key,typename Data>
//node* BSTtree<Key,Data>::L(node *rootA){
//    if(rootA == NULL){
//        return NULL;
//    }else{
//        node *x = new node;
//        x = rootA->right;
//        rootA->right = x->left;
//        x->left = rootA;
//        return x;
//    }
//}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//template <typename Key,typename Data>
//node* BSTtree<Key,Data>::R(node *rootA){
//    if(rootA == NULL){
//        return NULL;
//    }else{
//        node *x = new node;
//        x = rootA->left;
//        rootA->left = x->right;
//        x->right = rootA;
//        return x;
//    }
//}

//=================================================================================================================
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

#endif // BSTTREE_TMPL_H














