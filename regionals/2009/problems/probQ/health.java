import java.io.*;
import java.util.*;
/**
 * health club program
 * Laszlo Szuecs
 * 10/12/2009
 */
public class health
{
    public static void main( String[] args )
    {
         Scanner input = new Scanner(System.in);
         while (input.hasNextDouble())
         {
            ProblemInstance instance = new ProblemInstance();
            instance.read (input);
            System.out.printf("%.2f\n", instance.calculate());
          }
    }  // end main
}  // end class

class ProblemInstance
{
    double membership, admission;
    int requiredVisits,  // to earn one free visit
        actualVisits;
    public void read (Scanner input)
    {
       membership = input.nextDouble();
       admission = input.nextDouble();
       requiredVisits = input.nextInt();
       actualVisits = input.nextInt();
    }
    public double calculate()
    {
       int freeVisits = actualVisits / (requiredVisits + 1);
       double totalCost = membership + admission * (actualVisits - freeVisits);
       return totalCost / actualVisits;
    }
}  // end class ProblemInstance


