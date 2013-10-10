import java.io.*;
import java.util.*;
/**
 * Warren's papa program
 * Laszlo Szuecs
 * 9/10/2009
 *
 * The exact format of the input hasn't been specified yet.
 * For now assume: (1) there is only one problem instance, and
 * (2) the list of relationships is terminated by a blank line, and
 * (3) the list of questions has no terminator.
 *
 * Meaning of source and target in code:
 * If A is B's husband then B is the source and A is the target of the
 * relationship.
 *
 * 10/8/2009
 * Outcome now includes "unknown", in addition to "yes" or "no".
 * We assume that an unknown outcome can occur only if the target's
 * gender is unknown.
 *
 */
public class papa
{
    public static boolean debug = false;

    public static void main( String[] args )
    {
         Scanner input = new Scanner(System.in);
         String inputLine = null;
         StringTokenizer tokenizer = null;
         ProblemPapaInstance instance = new ProblemPapaInstance();

         // process the list of relationships
         try
         {
            inputLine = input.nextLine();
            while (inputLine.length() > 0)
            {
               if (debug)
                  System.out.println(inputLine);
               tokenizer = new StringTokenizer(inputLine, " '.", false);
               String targetName = tokenizer.nextToken();
               String throwAway = tokenizer.nextToken(); // the word "is"
               String sourceName = tokenizer.nextToken();
               throwAway = tokenizer.nextToken();  // the letter 's' after
                                                   // the apostrophe
               String relationship = tokenizer.nextToken();
               instance.defineRelationShip(targetName, sourceName,
                                           relationship);

               inputLine = input.nextLine();
            }
          }
          catch(java.util.NoSuchElementException iox  )
          {
          }
          if (debug)
          {  System.out.println();
             instance.printPeople();
             System.out.println();
          }

          // process the list of queries
          try
          {
             inputLine = input.nextLine();
             while (inputLine.length() > 0)
             {
                if (debug)
                   System.out.print(inputLine + "  ");
                tokenizer = new StringTokenizer(inputLine, " '?", false);
                String throwAway = tokenizer.nextToken(); // the word "is"
                String targetName = tokenizer.nextToken();
                String sourceName = tokenizer.nextToken();
                throwAway = tokenizer.nextToken();  // the letter 's' after
                                                    // the apostrophe
                String relationship = tokenizer.nextToken();

                if (debug)
                   System.out.println();
                instance.processQuery(targetName, sourceName, relationship);

                inputLine = input.nextLine();
             }
           }
           catch(java.util.NoSuchElementException iox  )
           {
           }
    }  // end main
}  // end class

class ProblemPapaInstance
{
    ArrayList<Person> people;
    Query query;

    public ProblemPapaInstance ()
    {
      people = new ArrayList<Person> ();
    }

    public void processQuery (String targetName,
                                   String sourceName,
                                   String relationShipString)
    {
      query = new Query(people,
                        targetName, sourceName,
                        utl.stringToInt(relationShipString));
      int verdict = query.answer();
      switch (verdict)
      {
         case utl.yes:
            System.out.println("yes");
            break;
         case utl.no:
            System.out.println("no");
            break;
         case utl.unknown:
            System.out.println("unknown");
            break;
      }
    }

    public void defineRelationShip(String targetName,
                                   String sourceName,
                                   String relationShipString)
    {

      int seekTarget = utl.search(people, targetName);
      Person targetPerson;
      if (seekTarget >= 0) // target already in people array
         targetPerson = people.get(seekTarget);
      else  // create new person and enter into people array
      {
         targetPerson = new Person(targetName);
         people.add(targetPerson);
      }

      int seekSource = utl.search(people, sourceName);
      Person sourcePerson;
      if (seekSource >= 0) // source already in people array
         sourcePerson = people.get(seekSource);
      else  // create new person and enter into people array
      {
         sourcePerson = new Person(sourceName);
         people.add(sourcePerson);
      }
      // in any event, establish the relationship
      int relationCode = utl.stringToInt(relationShipString);
      switch (relationCode)
      {
         case utl.wife:
         case utl.husband:
            sourcePerson.setRelationship(relationCode, targetPerson);
            defineInverseRelationship (sourcePerson, targetPerson,
                                       relationCode);
            verticalPropagate (sourcePerson, targetPerson);
            verticalPropagate (targetPerson, sourcePerson);
            break;
         case utl.mother:
         case utl.father:
            sourcePerson.setRelationship(relationCode, targetPerson);
            horizontalPropagate(targetPerson /* parent */,
                                sourcePerson /* child */);
            marryThroughCommonChild (sourcePerson /* child */);

            // If newly established child already had a parent ("other parent"),
            // make the newly established parent also a parent of
            // previously known children of the "other parent".
            // In other words, tie pre-exisitng siblings of child
            // to newly established parent.
            if (sourcePerson /* child */ . getParents().size() == 2)
               verticalPropagate
                   (sourcePerson.getParents().get(0) /* other parent */,
                    targetPerson /* newly established parent */);

            break;
         case utl.daughter:
         case utl.son:
            defineInverseRelationship (sourcePerson, targetPerson,
                                       relationCode);
            horizontalPropagate (sourcePerson /* parent */,
                                 targetPerson /* child */);
            marryThroughCommonChild (targetPerson /* child */);

            // If newly established child already had a parent ("other parent"),
            // make the newly established parent also a parent of
            // previously known children of the "other parent".
            // In other words, tie pre-exisitng siblings of child
            // to newly established parent.
            if (targetPerson /* child */ . getParents().size() == 2)
               verticalPropagate
                   (targetPerson.getParents().get(0) /* other parent */,
                    sourcePerson /* newly established parent */);
           break;
         default:
            break;
       }   // end switch
    }   // end method defineRelationship

    static void defineInverseRelationship(Person originalSource,
                                     Person originalTarget,
                                     int originalRelationCode)
    /*
     The given relationship is one of {wife, husband, daughter, son}.
     In the wife / husband case, the inverse is clearly vice - versa.

     But in the other two cases, the gender of the given source
     may not be known; therefore, the gender of the target of the inverse
     relationship may not be known, so we may have to resort to
     "parent" relationships. In such cases, future information may resolve
     the person's gender.
    */
    {
        Person inverseSource = originalTarget,
               inverseTarget = originalSource;
        switch (originalRelationCode)
        {
           case utl.husband:
             inverseSource.setRelationship(utl.wife, inverseTarget);
             break;
           case utl.wife:
             inverseSource.setRelationship(utl.husband, inverseTarget);
             break;
           case utl.daughter:
           case utl.son:
             inverseSource.setGender
                 (originalRelationCode == utl.daughter ?
                                           utl.female:
                                           utl.male);
             switch (inverseTarget.getGender())
             {
               case utl.male:
                 inverseSource.setRelationship(utl.father, inverseTarget);
                 break;
               case utl.female:
                 inverseSource.setRelationship( utl.mother, inverseTarget);
                 break;
               case utl.undetermined:
                 inverseSource.setRelationship(utl.parent, inverseTarget);
                 break;
              default:
                 break;
             }   // end inner switch
          default:
             break;
        }   // end outer switch

    }  // end method defineInverseRelationship

    /**
     * Side effect 1:
     * If a person has just been "named" the parent of a child, and if
     * that person has a spouse, then make the spouse also a parent of
     * the child.
     */
    void horizontalPropagate (Person givenParent, Person child)
    {
      Person spouse = givenParent.getSpouse();
      if (spouse == null)
        return;
      child.setRelationship(utl.parent, givenParent.getSpouse());
    }
    /**
     * Side effect 2:
     * For each child of the given parent, make the spouse also a parent.
     */
    void verticalPropagate(Person givenParent, Person spouse)
    {
      for (int childSeek = 0; childSeek < people.size(); childSeek++)
      {
        Person child = people.get(childSeek);
        ArrayList<Person> parents = child.getParents();
        if (parents.size() == 1 &&
          parents.get(0).getName().equals(givenParent.getName()))
          child.setRelationship(utl.parent, spouse);
      }
     }
     /**
      * Side effect 3:
      * If a child / parent relationship has been established and
      * the child already had a parent, then declare the two parents
      * a couple.
      */
     void marryThroughCommonChild(Person child)
     {
        ArrayList<Person> parents = child.getParents();
        if (parents.size() != 2)
          return;
        Person parent0 = parents.get(0);
        Person parent1 = parents.get(1);
        parent0.setRelationship(utl.spouse, parent1);
        parent1.setRelationship(utl.spouse, parent0);

        if (parent0.getGender() == utl.undetermined)
        {  if (parent1.getGender() == utl.male)
              parent0.setGender(utl.female);
            else if (parent1.getGender() == utl.female)
              parent0.setGender(utl.male);
        }

        if (parent1.getGender() == utl.undetermined)
        {  if (parent0.getGender() == utl.male)
              parent1.setGender(utl.female);
            else if (parent0.getGender() == utl.female)
              parent1.setGender(utl.male);
        }
     }
   public void printPeople()
   {
      for (int p = 0; p < people.size(); p++)
         people.get(p).print();
   }
}  // end class ProblemPapaInstance

class Query
{
   Person target, source;
   int relationCode;
   public Query (ArrayList<Person> people,
                 String targetStr, String sourceStr, int rel)
   {

     int targetIndex = utl.search(people, targetStr);
     if (targetIndex < 0)
       System.out.println ("unknown target in Query constructor");
     else
        target = people.get(targetIndex);

     int sourceIndex = utl.search(people, sourceStr);
     if (sourceIndex < 0)
       System.out.println ("unknown source in Query constructor");
     else
        source = people.get(sourceIndex);

     relationCode = rel;
   }
   public int answer ()
   {

     switch (relationCode)
     {
        case utl.wife:
           return isWife();
        case utl.husband:
           return isHusband();
        case utl.daughter:
           return isDaughter();
        case utl.son:
           return isSon();
        case utl.mother:
           return isMother();
        case utl.father:
           return isFather();
        case utl.grandDaughter:
           return isGrandDaughter();
        case utl.grandSon:
           return isGrandSon();
        case utl.grandMother:
           return isGrandMother();
        case utl.grandFather:
           return isGrandFather();
        case utl.niece:
           return isNiece();
        case utl.nephew:
           return isNephew();
       default:
           return -2;

     }  // end big switch
   }  // end method answer

  int isWife()
   {
      // establish spouse relationship
      if (!(source.getSpouse() != null &&
          source.getSpouse().getName().equals(target.getName())
          ||
          target.getSpouse() != null &&
          target.getSpouse().getName().equals(source.getName())
          ))
         return utl.no;

     // if at least one of the two people has the right gender, OK
     if ((source.getGender() == utl.male &&
     target.getGender() != utl.male
     ||
     source.getGender() != utl.female &&
     target.getGender() == utl.female
     ))
        return utl.yes;

     return utl.unknown;
   }


  int isHusband()
  {
    // establish spouse relationship
    if (!(source.getSpouse() != null &&
        source.getSpouse().getName().equals(target.getName())
        ||
        target.getSpouse() != null &&
        target.getSpouse().getName().equals(source.getName())
        ))
       return utl.no;
     // if at least one of the two people has the right gender, OK
     if ((source.getGender() == utl.female &&
        target.getGender() != utl.female
        ||
        source.getGender() != utl.male &&
        target.getGender() == utl.male
        ))
        return utl.yes;

      return utl.unknown;
  }   // end method isHusband

  int isDaughter()
  {
     // wrong gender
     if (target.getGender() == utl.male)
        return utl.no;

     // no parental relationship
     if (utl.search (target.getParents(), source.getName()) < 0)
        return utl.no;

     // now we have the parental relationship; let gender decide
     if (target.getGender() == utl.female)
        return utl.yes;
     else
        return utl.unknown;
  }

   int isSon()
   {
      // wrong gender
      if (target.getGender() == utl.female)
         return utl.no;

      // no parental relationship
      if (utl.search (target.getParents(), source.getName()) < 0)
          return utl.no;

      // now we have the parental relationship; let gender decide
      if (target.getGender() == utl.male)
         return utl.yes;
      else
         return utl.unknown;
   }

   int isMother()
   {
     // wrong gender
     if (target.getGender() == utl.male)
        return utl.no;

     // no parental relationship
     if (utl.search (source.getParents(), target.getName()) < 0)
        return utl.no;

     // now we have the parental relationship; let gender decide
     if (target.getGender() == utl.female)
        return utl.yes;
     else
        return utl.unknown;
   }

   int isFather()
   {
     // wrong gender
     if (target.getGender() == utl.female)
        return utl.no;

     // no parental relationship
     if (utl.search (source.getParents(), target.getName()) < 0)
        return utl.no;

     // now we have the parental relationship; let gender decide
     if (target.getGender() == utl.male)
        return utl.yes;
     else
        return utl.unknown;
   }

   int isGrandDaughter()
   {
     // wrong gender
     if (target.getGender() == utl.male)
        return utl.no;

     // no grandparental relationship
     if (!isGrandChild())
        return utl.no;

     // now we have the grandparental relationship; let gender decide
     if (target.getGender() == utl.female)
        return utl.yes;
     else
        return utl.unknown;
   }

   int isGrandSon()
   {
     // wrong gender
     if (target.getGender() == utl.female)
        return utl.no;

     // no grandparental relationship
     if (!isGrandChild())
        return utl.no;

     // now we have the grandparental relationship; let gender decide
     if (target.getGender() == utl.male)
        return utl.yes;
     else
        return utl.unknown;
   }

   boolean isGrandChild()
   {
      for (int p = 0; p < target.getParents().size(); p++)
      {
         Person parent = target.getParents().get(p);
         for (int gp = 0; gp < parent.getParents().size(); gp++)
         {
            if (parent.getParents().get(gp).getName().equals(source.getName()))
               return true;
         }
      }
      return false;
   }
   int isGrandMother()
   {
     // wrong gender
     if (target.getGender() == utl.male)
        return utl.no;

     // no grandparental relationship
     if (!isGrandParent())
        return utl.no;

     // now we have the grandparental relationship; let gender decide
     if (target.getGender() == utl.female)
        return utl.yes;
     else
        return utl.unknown;
   }

   int isGrandFather()
   {
     // wrong gender
     if (target.getGender() == utl.female)
        return utl.no;

     // no grandparental relationship
     if (!isGrandParent())
        return utl.no;

     // now we have the grandparental relationship; let gender decide
     if (target.getGender() == utl.male)
        return utl.yes;
     else
        return utl.unknown;
   }
   boolean isGrandParent()
   {
      for (int p = 0; p < source.getParents().size(); p++)
      {
         Person parent = source.getParents().get(p);
         for (int gp = 0; gp < parent.getParents().size(); gp++)
         {
            if (parent.getParents().get(gp).getName().equals(target.getName()))
               return true;
         }
      }
      return false;
   }
   int isNiece()
   {
     // wrong gender
     if (target.getGender() == utl.male)
         return utl.no;

     // no nice/nephew relationship
     if (!isNieceOrNephew())
        return utl.no;

     // now we have the nice/nephew relationship; let gender decide
     if (target.getGender() == utl.female)
        return utl.yes;
     else
        return utl.unknown;
   }
   int isNephew()
   {
     // wrong gender
     if (target.getGender() == utl.female)
         return utl.no;

     // no nice/nephew relationship
     if (!isNieceOrNephew())
        return utl.no;

     // now we have the nice/nephew relationship; let gender decide
     if (target.getGender() == utl.male)
        return utl.yes;
     else
        return utl.unknown;
   }
   boolean isNieceOrNephew()
   {
      for (int p = 0; p < target.getParents().size(); p++)
      {
         Person parent = target.getParents().get(p);
         for (int gp = 0; gp < parent.getParents().size(); gp++)
         {
            for (int q = 0; q < source.getParents().size(); q++)
               if (parent.getParents().get(gp).getName().equals
                   (source.getParents().get(q).getName()))
               return true;
         }
      }
      return false;
   }
}  // end class Query

class utl
{
    public static final int spouse = 0, wife = 1, husband = 2,
                            parent = 3, mother = 4, father = 5,
                            child = 6, daughter = 7, son = 8,
                            grandMother = 9, grandFather = 10,
                            grandDaughter = 11, grandSon = 12,
                            niece = 13, nephew = 14;
    public static final int undetermined = -1, female = 0, male = 1;
    public static final int unknown = -1, no = 0, yes = 1;


    public static String genderCodeToString (int code)
    {
       switch (code)
       {
          case undetermined:
             return "undetermined";
          case female:
             return "female";
          case male:
             return "male";
          default:
             return "unknown code";
       }
    }
    public static String relationCodeToString (int code)
    {
      switch (code)
        {
           case spouse:
             return "spouse";
           case wife:
             return "wife";
           case husband:
             return "husband";
           case child:
             return "child";
           case daughter:
             return "daughter";
           case son:
             return "son";
           case parent:
             return "parent";
           case mother:
             return "mother";
           case father:
             return "father";
           default:
             return "unknown code";
        }
    }

    public static int search (ArrayList<Person> people,
                              String name)
    {
      // just a linear search for now
      int seek = 0;
      while (seek < people.size())
      {
        if (people.get(seek).getName().equals(name))
          return seek;
        else
          seek++;
      }
      return -1;
    }

    public static int stringToInt (String str)
    {
      if (str.equals("wife"))
        return utl.wife;
      if (str.equals("husband"))
          return utl.husband;
      if (str.equals("daughter"))
          return utl.daughter;
      if (str.equals("son"))
          return utl.son;
      if (str.equals("mother"))
          return utl.mother;
      if (str.equals("father"))
          return utl.father;
      if (str.equals("grandmother"))
          return utl.grandMother;
      if (str.equals("grandfather"))
          return utl.grandFather;
      if (str.equals("granddaughter"))
          return utl.grandDaughter;
      if (str.equals("grandson"))
          return utl.grandSon;
      if (str.equals("niece"))
          return utl.niece;
      if (str.equals("nephew"))
          return utl.nephew;
      else
        return -1;
    }
    public static void addIfNotAlreadyInThere
        (ArrayList<Person> theList, Person pers)
    {
      int seek = search(theList, pers.name);
      if (seek == -1)
        theList.add(pers);
    }

}   //end class utl

class Person
{
    String name;
    int gender;
    Person spouse;
    ArrayList<Person> parents;
    public Person(String nm)
    {
      name = nm;
      gender = utl.undetermined;
      spouse = null;
      parents = new ArrayList<Person>(2);
    }
    /**
     * Enter a relationship in the "source" person's record.
     * The relationship must be of the type "spouse", "father", "mother"
     * or a less specific "parent".
     * Enter available gender information in either the source person's
     * or the target person's record.
     *
     * When the caller wishes to call this method to record a relationship
     * of the type "C is A's son / daughter", it must first "invert" the
     * relationship into the form "A is C's parent" and make use of any
     * available gender information.
    */
    public void setRelationship(int relationCode, Person targetPerson)
    {
      switch (relationCode)
      {
        case utl.spouse:
           spouse = targetPerson;
           break;
        case utl.wife:
           this.setGender (utl.male);  // only a male has a wife
           spouse = targetPerson;
           break;
        case utl.husband:
           this.setGender (utl.female);// only a female has a husband
           spouse = targetPerson;
           break;
        case utl.mother:
           utl.addIfNotAlreadyInThere (parents, targetPerson);
           targetPerson.setGender(utl.female);
           break;
        case utl.father:
           utl.addIfNotAlreadyInThere (parents, targetPerson);
           targetPerson.setGender(utl.male);
           break;
   /*
          The gender of the target
          (the original source) may not be known.
        */
        case utl.parent:
          utl.addIfNotAlreadyInThere (parents, targetPerson);
          break;
        default:
         break;
      }
    }
    public void setGender(int genderCode)
    {
      gender = genderCode;
    }
    public int getGender()
    {
      return gender;
    }
    public String getName ()
    {
      return name;
    }
    public Person getSpouse()
    {
      return spouse;
    }
    public ArrayList<Person> getParents()
    {
      return parents;
    }

    public void print()
    {
      System.out.print (getName() + ": ");
      System.out.println
           ("gender: " + utl.genderCodeToString(getGender()));
      System.out.print ("parents: ");
      for (int r = 0; r < getParents().size(); r++)
             System.out.print(getParents().get(r).getName() + "  ");
      System.out.println();
      System.out.print ("spouse: ");
      if (getSpouse() != null)
             System.out.print(getSpouse().getName());
      System.out.println();
      System.out.println("---------------------------------");
    }

} // end class Person
