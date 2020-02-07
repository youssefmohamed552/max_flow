#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <list>
#include <functional>
#include <stdio.h>


class Edge{
  private:
    int m_u, m_v, m_capacity, m_flow;
  public:
    Edge(const int u, const int v, const int capacity)
      : m_u(u), m_v(v), m_capacity(capacity), m_flow(0) {}
    ~Edge(){}
    int u() const { return m_u; }
    int v() const { return m_v; }
    int capacity() const { return m_capacity; }
    void set_capacity( const int c ) {m_capacity = c; }
    int flow() const { return m_flow; }
    void update_flow( const int f ) { m_flow += f; }
    bool operator==( const Edge& other) const {
      return ((m_u == other.u()) || (m_v == other.v()));
    }
};



  
class Graph{
  protected:
    int m_n, m_m, m_s, m_t;
    std::list<Edge> m_edges;
    std::unordered_map<int, std::list<Edge*>> m_adj_list;
  public:
    Graph(const int n, const int m, const int s, const int t, const std::list<Edge>& edges)
      : m_n(n), m_m(m), m_s(s), m_t(t), m_edges(edges)
    {
      // std::cout << "||||>>> graph created\n";
      // m_adj_list = new std::unordered_map<int,std::list<Edge*>*>();
      for(auto it = edges.begin(); it != edges.end(); it++){
        Edge e = *it;
        auto it_find_u = m_adj_list.find(e.u());
        if(it_find_u == m_adj_list.end()){
          m_adj_list[e.u()] = {new Edge(e.u(), e.v(), e.capacity())};
        }
        else{
          m_adj_list[e.u()].push_back(new Edge(e.u(), e.v(), e.capacity()));
        }
      }
      
    }
    ~Graph(){
      // std::cout << "Graph is destroyed\n" << std::endl;
    }
    int m() const { return m_m; }
    int n() const { return m_n; }
    int s() const { return m_s; }
    int t() const { return m_t; }
    std::unordered_map<int, std::list<Edge*>>& adj_list() { return m_adj_list; }
    std::list<Edge>& edges() { return m_edges; }

    void print(){
      std::cout << "Graph with m: " << m_m << " (edges) and n: " << m_n << " (vertex)" << std::endl;
      for( auto it_map = m_adj_list.begin(); it_map != m_adj_list.end(); it_map++){
        std::cout << "(" << it_map->first << "):";
        for(auto it_list = it_map->second.begin(); it_list != it_map->second.end(); it_list++){
          std::cout << " -> " << (*it_list)->v() << "(" << (*it_list)->flow() << "/" << (*it_list)->capacity() << ")"; 
        }
        std::cout << std::endl;
      }
    }
};

class ResidualGraph{
  private:
    Graph m_graph;
    std::unordered_map<int, std::list<Edge>> m_adj_list;
  public:
    ResidualGraph(Graph& graph)
      : m_graph(graph)
    {
      for(auto e: graph.edges()){
        auto find_u = m_adj_list.find(e.u());
        auto find_v = m_adj_list.find(e.v());
        if(find_u == m_adj_list.end()){
          m_adj_list[e.u()] = {Edge(e.u(), e.v(), e.capacity())};
        }
        else{
          m_adj_list[e.u()].push_back(Edge(e.u(), e.v(), e.capacity()));
        }
        if(find_v == m_adj_list.end()){
          m_adj_list[e.v()] = {Edge(e.v(), e.u(), 0)};
        }
        else{
          m_adj_list[e.v()].push_back(Edge(e.v(), e.u(), 0));
        }

      }
    }
    void update(Graph& g){
      for(auto g_it = g.adj_list().begin(); g_it != g.adj_list().end(); g_it++){
        for(auto e_it = g_it->second.begin(); e_it != g_it->second.end(); e_it++){
          Edge e = **e_it;
          auto f_u = m_adj_list.find(e.u());
          auto f_v = m_adj_list.find(e.v());

          // there is space to push more
          int residual_cap = e.capacity() - e.flow();
          for(auto temp_e = f_u->second.begin(); temp_e != f_u->second.end(); temp_e++ ){
            if(temp_e->v() == e.v()){
              temp_e->set_capacity(residual_cap);
            }
          }
          for(auto temp_e = f_v->second.begin(); temp_e !=  f_v->second.end(); temp_e++ ){
            if(temp_e->v() == e.u()){
              temp_e->set_capacity(e.flow());
            }
          }
        }
      }
    }

    std::unordered_map<int, std::list<Edge>>& adj_list(){ return m_adj_list; }

    void print(){
      std::cout << "printing the residual graph\n";
      for( auto it_map = m_adj_list.begin(); it_map != m_adj_list.end(); it_map++){
        std::cout << "(" << it_map->first << "):";
        for(auto it_list = it_map->second.begin(); it_list != it_map->second.end(); it_list++){
          std::cout << " -> " << it_list->v() << "(" << it_list->capacity() << ")"; 
        }
        std::cout << std::endl;
      }
    }
};

class FordFulkerson{
  private:
    int m_max_flow;
    Graph m_graph;
    ResidualGraph m_residual;
  public:
    FordFulkerson(Graph& graph)
      : m_max_flow(0), m_graph(graph), m_residual(ResidualGraph(graph))
    {
      // m_residual.print();
    }

    std::pair<std::list<int>, int> augmenting_path(int source, std::unordered_set<int>& visited){
      // std::cout << "trying to find the augmented path: " << source << " (source)" << std::endl;
      // add the edge to the visited list
      auto find_v = visited.find(source);
      if(find_v != visited.end()) return std::make_pair(std::list<int>(),0);
      visited.insert(source);
      // find the list of neigbouring edges from the source
      auto it_s = m_residual.adj_list().find(source);
      if(it_s == m_residual.adj_list().end()){
      // if(it_s == m_residual.adj_list().end() || it_s->second.size()){
        std::cout << "This element doesn't exist in the list or there are no more neighbouring elements\n";
        return std::make_pair(std::list<int>(),0);
      }
      // loop through the list of neighbouring edges until finding an edge with a capacity > 0
      
      for(auto it_n = it_s->second.begin(); it_n != it_s->second.end(); it_n++){
        // check the capacity is zero or the neighbour had been visited before
        auto find_v = visited.find(it_n->v());
        if(find_v != visited.end() || it_n->capacity() == 0) continue;
        // append the source to augmented_path given the new found vertex as the new source
        if(it_n->v() == m_graph.t()){
          return std::make_pair<std::list<int>,int>({source, it_n->v()}, it_n->capacity());
        }
        std::pair<std::list<int>, int> p = augmenting_path(it_n->v(),visited);
        std::list<int> l = p.first;
        if(l.back() != m_graph.t()) continue;
        std::list<int> new_list = {source};
        new_list.insert(new_list.end(), l.begin(), l.end());
        return std::make_pair(new_list,(p.second > it_n->capacity()? it_n->capacity() : p.second));
      }
      return std::make_pair(std::list<int>(),0);
    }

    bool augment_path(std::list<int>& path, int flow){
      // std::cout << "augmenting path with flow " << flow << "\n";
      int node = path.front();
      path.pop_front();
      // for(auto it_p = path.begin(); it_p != path.end(); it_p++){
      for(int v: path){
        // if(*it_p == m_graph.s()) continue;
        // std::cout << *it_p << std::endl;
        std::list<Edge*> l = m_graph.adj_list()[node];
        int f = flow;

        // find the regular edge
        auto it_n = l.begin();
        while(it_n != l.end() && (*it_n)->v() != v){
          it_n++;
        }

        // find the reverse edge
        if(it_n == l.end()){
          l = m_graph.adj_list()[v];
          it_n = l.begin();
          while(it_n != l.end() && (*it_n)->v() != node){
            it_n++;
          }
          if(it_n == l.end()) return false;
          f = -1 * flow;
        }

        // std::cout << "updating flow" << std::endl;
        (*it_n)->update_flow(f);
        // std::cout << "new flow " <<  (*it_n)->flow() << std::endl;
        node = v;
      }
      return true;
    }

    void print_path(std::list<int> path , int flow){
        std::cout << "printing the path with flow of : " << flow << " \n";
        for(auto it_e = path.begin(); it_e != path.end(); it_e++){
          std::cout << *it_e << " ";
        }
        std::cout << std::endl;
    }


    int run(){
      // while there is still a valid path
      std::pair<std::list<int>, int> p;
      std::list<int> path;
      int flow = 0;

      while(true){
        // find a path
        std::unordered_set<int> visited;
        p = augmenting_path(m_graph.s(), visited);
        if(p.second == 0 || p.first.back() != m_graph.t()) break;
        path = p.first;

        flow += p.second;
        
        // augment the graph over the flow
        augment_path(path, p.second);
        // m_graph.print();
        // update the residual graph
        m_residual.update(m_graph);
        // m_residual.print();
      // }while(p.second > 0 && (path.back() == m_graph.t()));
      }
      return flow;
    }
   


};




int main(int argc, char* argv[]){
  // get user input
  int k = 0, n = 0, m = 0, s = 0, t = 0;
  std::list<Edge> edges;
  // std::cout << " Hello I am supposed to be calculating the max flow in a program " << std::endl;
  std::cin >> k;
  // std::cout << "k:= " << k << std::endl;

  for(int i = 0; i < k; i++){
    std::cin >> n >> m >> s >> t;
    for(int j = 0; j < m; j++){
      int u, v, c;
      std::cin >> u >> v >> c;
      edges.push_back(Edge(u, v, c));
    }
    // make the graph
    Graph graph(n, m, s, t, edges);
    // graph.print();

    FordFulkerson ff(graph);
    int max_flow = ff.run();
    // std::cout << "max flow is found to be : " << max_flow << std::endl;
    std::cout << max_flow << std::endl;

    // ResidualGraph residual(graph);
    // residual.print();

  }
  return 1;
}
