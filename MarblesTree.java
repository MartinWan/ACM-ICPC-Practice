import java.util.*;

// problem https://open.kattis.com/problems/marblestree

class Node {
  public Node parent;
  public List<Node> children;
  public int marbles;
  public int label;
}

public class MarblesTree {
  
  public static int minBalanceMoves(Node root) {
    List<Node> L = levelOrder(root);
    Collections.reverse(L);
    
    int moveCount = 0;

    for (Node node : L) {
      if (node == root) break;

      if (node.marbles == 0) {
        node.parent.marbles--;
        moveCount++;
      } else if (node.marbles > 1) {
        node.parent.marbles += node.marbles - 1;
        moveCount += node.marbles - 1;
      } else if (node.marbles < 0) {
        node.parent.marbles -= -node.marbles + 1;
        moveCount += -node.marbles + 1;
      }
    }

    return moveCount;
  }

  public static List<Node> levelOrder(Node root) {
    List<Node> L = new LinkedList<>();

    Queue<Node> Q = new LinkedList<>();
    Q.add(root);

    while (!Q.isEmpty()) {
      Node node = Q.poll();
      L.add(node);
     
      for (Node child : node.children) {
        Q.add(child);
      }
    }

    return L;
  }
  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();

    while (n != 0) {
      Node[] nodes = new Node[n+1];
      
      for (int i = 1; i <= n; i++)
        nodes[i] = new Node();

      for (int j = 0; j < n; j++) {
        int v = in.nextInt();
        int m = in.nextInt();
        int d = in.nextInt();
 
        nodes[v].label = v;
        nodes[v].marbles = m;
        nodes[v].children = new LinkedList<>();
        
        for (int i = 0; i < d; i++) {
          int childLabel = in.nextInt();
          nodes[v].children.add(nodes[childLabel]);
          nodes[childLabel].parent = nodes[v];
        }
      }


      Node root = nodes[1];
      for (int i = 1; i <= n; i++) 
        if (nodes[i].parent == null)
          root = nodes[i];

      System.out.println(minBalanceMoves(root));

      n = in.nextInt();
    }
  }
}

