#include <stdio.h>
#include <math.h>
# define MtabX_COLUMN 80
#include <stdint.h>
#include <assert.h> 
#include <time.h>
#include <string.h> 
#include <stdbool.h>


void make_heap(int* tab, unsigned n);
void heapify(int* tab, unsigned n, unsigned pos);
void build_heap(int* tab, unsigned n);
void print_space(FILE* out, int space, int space_p, int max_size);

//-------------print_int_array------------------------------
unsigned int_width(double i)
{
unsigned nb = 0;
  if (i > 0)
  { 
    nb = log10(i) + 1;
  } 
  else if (i < 0)
  { 
    i = i * (-1); 
    nb = log10((double)i) + 2;
  }     
  else
  {
    nb = 1;
  }
return nb;
}

unsigned ints_width(const int* tab, unsigned count)
{
unsigned nb[count];
unsigned max_nb = 0;

  if(tab != NULL)
  {
    for (unsigned i = 0; i < count; ++i)
    {
      nb[i] = int_width(tab[i]);
 		}

  for(unsigned i = 0; i < count; ++i)
  {
    if(max_nb < nb[i])
    {
      max_nb = nb[i];
    }
  }
  return max_nb;
  }
return -1;
}

void printWhiteSpace(FILE* out, unsigned int count)
{
  for (unsigned int i = 0; i < count ; ++i)
  {
    fprintf(out, " ");
  }
}

void printOneInt(FILE*out, const int num, const unsigned int int_width, const unsigned int max_width)
{
  printWhiteSpace(out, max_width - int_width);
  fprintf(out, "%d", num);
}

void print_int_array(FILE* out, const int* tab, unsigned count)
{
  unsigned int max_width = ints_width(tab, count);
 // unsigned int leadingIndex = 0;
  unsigned int numOfIntsInTheRow;
 	unsigned int indexWidth = int_width(count - 1);
	for (unsigned int i = 0; i < count;)
  {
    numOfIntsInTheRow = (MtabX_COLUMN - int_width(count - 1) - 2) / (max_width + 1);
    printWhiteSpace(out, indexWidth - int_width(i));
    fprintf(out, "[");
    fprintf(out, "%d", i);
    fprintf(out, "]");
    for (unsigned int j = i; j < i + numOfIntsInTheRow && j < count; ++j)
    {
      fprintf(out, " ");
      printOneInt(out, tab[j], int_width(tab[j]), max_width);
    }
    fprintf(out, "\n");
    i += numOfIntsInTheRow;
  }
}

void insert_sort(int* tab, unsigned count)
{
int i, j;
int temp;

  for(i = 0; i < count; ++i)
  {
      temp = *(tab + i);
      for (j = i; j > 0 && *(tab + j - 1) > temp; j--)
      {
        *(tab + j) = *(tab + j - 1);
      }
      *(tab + j) = temp;
  }
}



//-------------print_int_array------------------------------

//-------------make_heap------------------------------------
/*void make_heap(int* tab, unsigned n)
{
	build_heap(tab, n);
	for(int i = n; i >= 2; i--)
  {
    int temp = tab[i];
    tab[i] = tab[1];
    tab[1] = temp;
    heapify(tab, i-1, 1);
  }
}*/

void make_heap(int* tab, unsigned n)
{
	for (int i = n/2; i >= 0; i--)
	{
		heapify(tab, n, i);
	}
}

//n ==> length; pos == position (i in make_heap)
void heapify(int* tab, unsigned n, unsigned pos)
{
	int leftc = 2 * pos +1;
	int	rightc = 2 * pos + 2;
	unsigned largest_nb = 0;

//printf("yolo\n");
	if (leftc < n && tab[pos] < tab[leftc])
	{
		largest_nb = leftc;
		//printf("%i\n", largest_nb);
	}
	else
	largest_nb = pos;
	
  if (rightc < n && tab[largest_nb] < tab[rightc])
	{
//		printf("%i\n", largest_nb);
		largest_nb = rightc;
	}
	
/*	if (rightc <= pos && tab[rightc] > tab[largest_nb])
	{
		largest_nb = rightc;
	}*/

	if (pos != largest_nb)
	{	
		//swp(largest_nb and tab[i])
		int temp = tab[largest_nb];
		tab[largest_nb] = tab[pos];
		tab[pos] = temp;
		
		heapify(tab, n, largest_nb);
	}
}

//------------make_heap------------------------------------

//------------check_heap------------------------------------

bool check_heap(int* heap, unsigned n)
{
	for (int i = 0; i < n / 2; i++)
	{
		if ( n != 0 && heap[i] < heap[2 * i + 1])	
			return false;
		else if(n != 0 && heap[i] < heap[2 * i + 2])
			return false;
	}
return true;
}

//------------check_heap------------------------------------


//-------------pretty print heap-----------------------------
void pretty_print_heap(FILE* out, const int* v, int n)
{
	int depth = 0 - 1;
	int max_size = ints_width(v,n);
	//make_heap((int*)v, n);
	//this "for" is used for \n
	for (int i = 0; i < n; i = 2 * i + 1)
	{
		depth++;
		//printf("depth is %i\n", depth);
	}
	
	//size of last line
	int t = (ints_width(v,n) + 1) * pow(2, depth);
	//printf("%i\n", t);	

	for(int i = 0; i < n; i++)
	{
		int c = i + 1;
		int space = t / c - max_size;
    print_space(out, space, int_width(v[i]), max_size);
		/*for (int i = 0; i < padding_space + max_side - int_width(v[i]); i++)
			fprintf(out, " ");*/
		fprintf(out, "%i", v[i]);
		
		//control the line: index + 1 <= 2 ^ depth - 1 
		int j = 0;	
		for(j = i; j < 2 * i && j < n - 1 ; j++)
		{
			print_space(out, space * 2, int_width(v[j+1]), max_size);
			fprintf(out,"%i", v[j + 1]);
		}
	//change line
	i = j; 	
	fprintf(out,"\n");
	}
}
void print_space(FILE* out, int space, int space_p, int max_size)

{
	int padding_space = space / 2;
	//printf("padding_space is %i\n", padding_space);
	for (int i = 0; i < padding_space + max_size - space_p; i++)
	{
		//printf("dddd");
		fprintf(out," ");
	}	
}

//-------------pretty print heap-----------------------------

//--------------pop_heap------------------------------------
int pop_heap(int* heap, unsigned* n)
{
	int ret = heap[0];
	int size = *n;
	int i = 0;

	while (i * 2 + 1 <= size)
	{
		int a = i * 2 + 1;
		int b = i * 2 + 2;
		if (b < size && heap[b] < heap[a])
		{
			a = b;
		}
	
		if (heap[a] >= size)
		{break;}
		
		heap[i] = heap[a];
		i = a;
	}
	heap[i] = size;
	return ret;
}

//--------------pop_heap------------------------------------


//-------------heap_sort-------------------------------------
void heap_sort(int* tab, unsigned n)
{
	make_heap(tab, n);
  insert_sort(tab, n);
}

//-------------heap_sort-------------------------------------
int main(void)
{
/*
int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
unsigned asize = sizeof(a) / sizeof(*a);
make_heap(a, asize);
puts("output:");
print_int_array(stdout, a, asize);
*/


/*test for check heap---------------
int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
unsigned asize = sizeof(a) / sizeof(*a);
printf("input is %sa heap\n", check_heap(a, asize) ? "" : "not ");
make_heap(a, asize);
printf("output is %sa heap\n", check_heap(a, asize) ? "" : "not ");
//-------------------------------------------*/

/*test for pretty tree----------------------------

int a[] = { 16, 2, -3, 42, 54, 65, 73, 8, 90, 10, 11, 12, 13 };
unsigned asize = sizeof(a) / sizeof(*a);
make_heap(a, asize);
puts("Look Ma! I drew a tree!");
pretty_print_heap(stdout, a, asize);
//test for pretty tree----------------------------*/

//test for pop_heap---------------------------------
int a[] = { 123, 0, 33, 42, 544, 165, -73, 228 };
unsigned asize = sizeof(a) / sizeof(*a);
make_heap(a, asize);
puts("init");
pretty_print_heap(stdout, a, asize);
for (unsigned i = 0; i < 5; ++i)
  {
     printf("pop_heap() == %d\n", pop_heap(a, &asize));
     pretty_print_heap(stdout, a, asize);
  }




//test for pop_heap---------------------------------


/*test for heap sorted-------------------------------
int a[] = { 123, 0, 33, 42, 544, 165, -73, 228, -99, -10, -11, 912, -13, 12, 345 };
unsigned asize = sizeof(a) / sizeof(*a);
puts("before");
print_int_array(stdout, a, asize);
heap_sort(a, asize);
puts("after");
print_int_array(stdout, a, asize);
//test for heap sorted-------------------------------*/


return 0;
}
