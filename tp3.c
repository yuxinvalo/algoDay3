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
//int leftc = 0;
//int rightc = 0;
	
	for (int i = n/2; i >= 1; i--)
	{
		//printf("i is %i\n", i);
		//leftc = 2i;
		//rightc = 2i+1;
		//printf("left:%i rignt:%i\n", leftc, rightc);
		if ( n != 0 && heap[i] >= heap[2 * i + 1])	
		{
		//	printf("%i\n", leftc);
			i = i / 2 +1;
		} 
		else
			return false;

		if(n != 0 && heap[i] >= heap[2 * i + 2])
		{
			i = i / 2 + 2;
		}
		else 
			return false;
	}
return true;
}

//------------check_heap------------------------------------


int main(void)
{
/*
int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
unsigned asize = sizeof(a) / sizeof(*a);
make_heap(a, asize);
puts("output:");
print_int_array(stdout, a, asize);
*/


//test for check heap---------------
int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
unsigned asize = sizeof(a) / sizeof(*a);
printf("input is %sa heap\n", check_heap(a, asize) ? "" : "not ");
make_heap(a, asize);
printf("output is %sa heap\n", check_heap(a, asize) ? "" : "not ");
//-------------------------------------------


return 0;
}
