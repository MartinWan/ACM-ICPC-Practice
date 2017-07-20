import java.util.*;

// https://open.kattis.com/problems/classy

class Person implements Comparable {
  public List<String> class_;
  public String name;

  public Person(String name, List<String> class_) {
    this.name = name;
    this.class_ = class_;
  }

  public int compareTo(Object other) {
    Person p1 = (Person) this;
    Person p2 = (Person) other;

    int N = Math.max(p1.class_.size(), p2.class_.size());

    for (int i = 0; i < N; i++) {
      String token1 = i >= p1.class_.size() ? "middle" : p1.class_.get(i);
      String token2 = i >= p2.class_.size() ? "middle" : p2.class_.get(i);
      
      if (!token1.equals(token2)) {
        int t1 = toNumber(token1);
        int t2 = toNumber(token2);

        if (t1 > t2)
          return 1;
        else 
          return -1;
      }
    }

    return -p1.name.compareTo(p2.name);
  }

  private int toNumber(String class_) {
    if (class_.equals("lower"))
      return 0;
    else if (class_.equals("middle"))
      return 1;
    else
      return 2;
  }
}

class Classy {  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int T = in.nextInt();

    for (int i = 0; i < T; i++) {
      int n = in.nextInt();
      Person[] persons = new Person[n];

      for (int j = 0; j < n; j++) {
        String name = in.next().replace(":", "");
        List<String> class_ = Arrays.asList(in.next().split("-"));

        Collections.reverse(class_);
        persons[j] = new Person(name, class_);
        in.next();
      }
      Arrays.sort(persons);
      
      for (int j = n - 1; j >= 0; j--) {
        System.out.println(persons[j].name);
      }

      System.out.println("==============================");
    }

  }
}
