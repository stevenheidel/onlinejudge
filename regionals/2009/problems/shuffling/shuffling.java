import java.io.*;
import java.util.*;

/**
 * Howard's Card Shuffling problem
 *
 * Literal translation of Howard's C++ solution into Java.
 * Added class MyLong in order to simulate parameter passing
 * by reference.
 * Used java's 64-bit signed "long" data type in place of the C++ "long long"
 * data type. Java does not have unsigned data types.
 *
 * 9/30/2009
 *
 */
public class shuffling
{
    public static void main( String[] args )
    {    Scanner input;
         input = new Scanner(System.in);
         int N = input.nextInt();   // number of towers
         while (N > 0)
         {
            ProblemShufflingInstance instance = new ProblemShufflingInstance(N);
            instance.read(input);
            System.out.println(instance.solve());

            // next instance
            N = input.nextInt();
         }

    }  // end main
}  // end class

class ProblemShufflingInstance
{
   int N;
   int [] once, want;

   public ProblemShufflingInstance (int n)
   {
      N = n;
      once = new int[N];
      want = new int[N];
   }
   void read(Scanner input)
   {
      /*
        Subtract 1 from values read. We will be working with
        indices 0 .. N-1 in the rest of the program
      */
      for (int i = 0; i < N; i++)
         once [i] = input.nextInt() - 1;
      for (int i = 0; i < N; i++)
          want [i] = input.nextInt() - 1;
   }

   public long solve()
   {
      int[] perm = new int[N];
      long[] cycle_len = new long[N];
      long[] rem = new long[N];

      // compute permutation so perm[k] => position k in shuffling
      for (int i = 0; i < N; i++)
         perm[once[i]] = i;

      // now trace each element
      for (int i = 0; i < N; i++)
      {
         int count = 1;
         int location = perm[i];
         rem[i] = (want[location] == i) ? 1 : -1;

         // must repeat after N+1 steps
         while (location != i && count <= N+1)
         {
             location = perm[location];
             count++;
             if (want[location] == i)
                rem[i] = count;
         }
         cycle_len[i] = count;

         // impossible
         if (rem[i] == -1)
            return -1;
         rem[i] %= cycle_len[i];
       }
       // apply Chinese remaindering
       return chrem(N, rem, cycle_len);
   }   // end method solve

   long chrem (int N, long[] rem, long[] mod)
   {
      long rem_so_far = rem[0];
      long mod_so_far = mod[0];

      for (int i = 1; i < N; i++)
      {
         // since x = s * mod_so_far + rem_so_far
         //         = t * mod[i] + rem[i]
         //
         // we solve diophantine equation:
         //
         // mod_so_far * s - mod[i] * t = rem[i] - rem_so_far
         //
         long a = mod_so_far, b = -mod[i], c = rem[i] - rem_so_far;

         // Laszlo:
         // Simulate "pass by reference" by passing objects to gcd method:
         MyLong s0 = new MyLong(0), t0 = new MyLong(0);
         long g = gcd(a, b, s0, t0);
         if (c % g != 0)
            return -1;   // no solution

         s0.multiply(c / g);
         t0.multiply(c / g);

         // general solution to the equation is:
         //
         // a * (s0 + k*(b/g)) + b * (t0 - k*(a/g)) = c
         //
         // so we have:
         //
         // x =   a  * (s0 + k*(b/g)) + rem_so_far
         // x = (-b) * (t0 - k*(a/g)) + rem[i]
         //
         // Note: b = -mod[i]
         //
         // so we have:
         //
         // x = (a/g)*b * k + rem_so_far + mod_so_far * s0
         //   = (b/g)*a * k + rem[i] + mod[i] * t0
         long limit = ((long)1 << 63) - 1;
         // the test below is perhaps a little bit conservative but
         // should be okay
         if ((s0.getValue() > 0 && limit / s0.getValue() < mod_so_far) ||
             (s0.getValue() < 0 && limit / s0.getValue() > mod_so_far) ||
             limit - rem_so_far < mod_so_far * s0.getValue() ||
             mod[i] > limit / (mod_so_far / g))
         {
            System.out.println("mod_so_far = " + mod_so_far);
            System.out.println("s0 = " + s0.getValue());
            System.out.println("rem_so_far = " + rem_so_far);
            System.out.println("Bad input: modulus too big");
            return -1;
         }

         rem_so_far += mod_so_far * s0.getValue();
         mod_so_far = (mod_so_far/g) * mod[i];
         rem_so_far %= mod_so_far;
         if (rem_so_far < 0)
            rem_so_far += mod_so_far;

         assert(rem_so_far < limit);
      }   // end "for"
      return rem_so_far;
   }   // end method chrem

   long gcd (long a, long b, MyLong s, MyLong t)
   {
      long r, r1, r2, a1, a2, b1, b2, q;

      /* unnecessary if a, b >= 0 */
      if (a < 0)
      {
         r = gcd(-a, b, s, t);
         s.multiply(-1);
         return r;
      }
      if (b < 0)
      {
         r = gcd(a, -b, s, t);
         t.multiply(-1);
         return r;
      }
      a1 = b2 = 1;
      a2 = b1 = 0;
      while (b != 0)
      {
         q = a / b;
         r = a % b;
         r1 = a1 - q*b1;
         r2 = a2 - q*b2;
         a = b;
         a1 = b1;
         a2 = b2;
         b = r;
         b1 = r1;
         b2 = r2;
      }
      s.setValue(a1);
      t.setValue(a2);
      return a;

   }
}  // end class ProblemShufflingInstance

/**
  * The Long class in package java.lang doesn't have a mutator method.
  * It is a "final" class, meaning that the programmer can't extend it to
  * include a mutator method.
*/
class MyLong
{
   long value;
   public MyLong (long val)
   {
      value = val;
   }
   /**
    *  accessor method
    */
   public long getValue ()
   {
      return value;
   }
   /**
    *  mutator method
    */
   public void setValue (long val)
   {
      value = val;
   }
   /**
    * multiplicator (more convenient to use than accessor AND mutator)
    */
   public void multiply (long multiplier)
   {
      value *= multiplier;
   }
}
