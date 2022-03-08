
__kernel void Compute(__global const long* number, __global int* result)
{
     size_t i = get_global_id(0);

     if(i == 0 || i == 1 || *number % i == 0)
     {
          *result = 0;
     }
     else 
     {
          *result = 1;
     }
}