#include <stdint.h>
#include  "vcop_sort_cn.h"

int32_t vcop_sort_cn(uint32_t elements, uint32_t *arr, int32_t *beg, int32_t *end)
{
  uint32_t piv;
  int32_t L, R;
  int32_t i;

  beg[0]=0;
  end[0]=elements;
  i=0;
  while (i>=0)
  {
    L=beg[i];
    R=end[i]-1;

    if (L<R)
    {
      piv=arr[L];
      if (i==(1000-1))
      {
        /* <ln_offset:1 MISRA Rule 14.7: reviewer name: JG date: 25-October-2011 reason: ok. */
        return -1;
      }
      while (L<R)
      {
        while ((arr[R]>=piv) && (L<R))
        {
          R--;
        }
        if (L<R)
        {
          arr[L++]=arr[R];
        }

        while ((arr[L]<=piv) && (L<R))
        {
          L++;
        }
        if (L<R)
        {
          arr[R--]=arr[L];
        }
      }
      arr[L]=piv;
      beg[i+1]=L+1;
      end[i+1]=end[i];
      end[i++]=L;
    }
    else
    {
      i--;
    }
  }

  return 0;
}
