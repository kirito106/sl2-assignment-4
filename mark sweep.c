#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    bool mark;//for marking the nodes to use mark and sweep mechanism
    int ref_count;//reference count mechanism
    struct node *next_1;
    struct node *next_2;
    struct node *next_3;
    //Maximum three links are shown in the diagram
    
}Node;

 Node *point_array[8];

void display_node(int i)
{
	printf("value=%d\t reference_count=%d freed_size=%d\n",point_array[i]->data,point_array[i]->ref_count,sizeof(Node));
}//function to display reference count and freed size

void set_edge(int so,int address1,int address2,int address3)
{
	if(address1!=-1)
	{
		point_array[so]->next_1=point_array[address1];
		point_array[address1]->ref_count+=1;
	}
	if(address2!=-1)
	{
		point_array[so]->next_2=point_array[address2];
		point_array[address2]->ref_count+=1;
	}
	if(address3!=-1)
	{
		point_array[so]->next_3=point_array[address3];
		point_array[address3]->ref_count+=1;
	}
	
}
void display_all_nodes(Node* root)
{
	if(root!=NULL)
	{
		printf("value=%d:ref_count=%d\n",root->data,root->ref_count);
	}
	if(root==NULL)
	{
		return;
	}
	display_all_nodes(root->next_1);
	display_all_nodes(root->next_2);
	display_all_nodes(root->next_3);
}
void adjacency_list()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if(point_array[i]!=NULL)
		{
			printf("Value=%d: ",point_array[i]->data);
			if(point_array[i]->next_1!=NULL)
			{
				printf("%d ->",point_array[i]->next_1->data);
			}
			if(point_array[i]->next_2!=NULL)
			{
				printf("%d ->",point_array[i]->next_2->data);
			}
			if(point_array[i]->next_3!=NULL)
			{
				printf("%d ->",point_array[i]->next_3->data);
			}
			printf("NULL\n");
		}
	}
}
int rootpresent(Node* root1,Node* temp)
{
	if(root1==NULL)
	{
		return 0;
	}
	if(root1->data==temp->data)
	{
		return 1;
	}
	
	if(rootpresent(root1->next_1,temp))
	{
		return 1;
	}
	
	if(rootpresent(root1->next_2,temp))
	{
		return 1;
	}
	if(rootpresent(root1->next_3,temp))
	{
		return 1;
	}
 return 0;
}

void adjacency_Matrix()
{
	int adm[8][8];
	int i,j,k;
	
	for(i=0;i<8;i++)		//initialising all indices values to 0
	{
		for(j=0;j<8;j++)
		{
			adm[i][j]=0;
		}	
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			
		if(point_array[j]!=NULL&&point_array[i]!=NULL)
		{
			
			if(point_array[i]->next_1!=NULL)
			{
				if(point_array[i]->next_1->data==point_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(point_array[i]->next_2!=NULL)
			{
				if(point_array[i]->next_2->data==point_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(point_array[i]->next_3!=NULL)
			{
				if(point_array[i]->next_3->data==point_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
		}
		
		}
	}
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d ",adm[i][j]);		//printing the adjacency matrix
		}
		printf("\n");
	}
}
void mark_the_Nodes(Node*root,int i,int j)
{
    Node *current, *pre;

    current = root;
        
    while (current != NULL) 
    {
  
        if (current->next_1== NULL) 
        {
            current->mark=true;
            current = current->next_2;
        }   
        else 
        {
            pre = current->next_1;
            while ((pre->next_2 != NULL) && (pre->next_2 != current))
            {
            	pre = pre->next_2;
			}
                
            if (pre->next_2 == NULL) 
            {
                pre->next_2 = current;
                current = current->next_1;
            }
            else 
            {
                pre->next_2 = NULL;
                current->mark=true;
                current = current->next_2;
            } 
        }
    }     
    current = root;
    while (current != NULL) 
    {
  
        if (current->next_1== NULL) 
        {
            current->mark=true;
            current = current->next_3;
        }   
        else 
        {
            pre = current->next_1;
            while ((pre->next_3 != NULL) && (pre->next_3 != current))
            {
            	pre = pre->next_3;
			}
                
            if (pre->next_3 == NULL) 
            {
                pre->next_3 = current;
                current = current->next_1;
            }
            else 
            {
                pre->next_3 = NULL;
                current->mark=true;
                current = current->next_3;
            } 
        }
    }  
    
}
void mark_met(Node* root)
{
	if(root!=NULL)
	{
		root->mark=true;
	}
	if(root==NULL)
	{
		return;
	}
	mark_met(root->next_1);
	mark_met(root->next_2);
	mark_met(root->next_3);
}
void sweep_met()
{	int i;
	for(i=0;i<8;i++)
	{
		if(point_array[i]->mark==false)
		{
			if(point_array[i]->next_1!=NULL)
			{
				point_array[i]->next_1->ref_count-=1;
			}
			if(point_array[i]->next_2!=NULL)
			{
				point_array[i]->next_2->ref_count-=1;
			}
			if(point_array[i]->next_3!=NULL)
			{
				point_array[i]->next_3->ref_count-=1;
			}
			printf("Garbage:");
			display_node(i);
			free(point_array[i]);
			point_array[i]=NULL;
		}
	}
}
int main()
{		
	int val[]={1,2,3,5,7,8,9,10};
	int i;
	for( i=0;i<8;i++)
	{
		Node* newNode =(Node*)malloc(sizeof(Node));
		newNode->data=val[i];
		newNode->next_1=NULL;
		newNode->next_2=NULL;
		newNode->next_3=NULL;
		newNode->ref_count=0;
		newNode->mark=false;		
		point_array[i]=newNode;
	}
	
	Node*root1=point_array[3];
	point_array[3]->ref_count+=1;
	Node*root2=point_array[0];
	point_array[0]->ref_count+=1;
	
	set_edge(0,1,6,7);
	set_edge(2,5,7,-1);
	set_edge(3,0,-1,-1);
	set_edge(4,0,5,-1);
	set_edge(5,6,-1,-1);
	
	printf("Root of value 3:");
	display_node(2);
	
	printf("\nAll nodes through Root-1:\n");
	display_all_nodes(root1);
	
	printf("\nAll nodes through Root-2:\n");
	display_all_nodes(root2);
	
	printf("\n\nAdjacency list :\n");//Displaying Adjacency list of the nodes with corresponding value or vertex
	adjacency_list();
	
	printf("\n\nAdjacency matrix:\n");//Displaying Adjacency Matrix of the nodes rather than root 1 and root 2
	adjacency_Matrix();
	
	printf("\nCalling the mark and sweep garbage collector\n");
	//mark_the_Nodes(root1,0,1);
	mark_met(root1);
	sweep_met();
	
	printf("\n\nAdjacency list after removal of garbage:\n");
	adjacency_list();
	
	printf("\n\nAdjacency matrix after removal of garbage:\n");
	adjacency_Matrix();
	

}
