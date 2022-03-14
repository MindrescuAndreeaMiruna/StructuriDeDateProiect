#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
typedef std::pair<int, int> ii; 

/**************************** HeapSort ***************************/

class HeapSort{
private:
    std::vector<int> h;
    int n;
public:
    HeapSort(std::vector<int>&);
    void insert_heap(int);
    int get_min_heap();
    void delete_heap();
    std::vector<int> sort();
};

HeapSort::HeapSort(std::vector<int>& v){
    n = 0;
    h.push_back(0);
    for(auto x: v)
        this->insert_heap(x);
}

void HeapSort::insert_heap(int x){
    int tata, fiu;
    ++ n;
    h.push_back(x);
    fiu = n;
    while(fiu > 1){
        tata = (fiu >> 1);
        if(h[tata] > h[fiu]){
            int aux = h[tata];
            h[tata] = h[fiu];
            h[fiu] = aux;
        } else break;
        fiu >>= 1;
    }
}

int HeapSort::get_min_heap(){
    return h[1];
}

void HeapSort::delete_heap(){
    int fiu, tata;
    h[1] = h[n];
    n --;
    h.pop_back();
    tata = 1;
    while(tata <= (n >> 1)){
        fiu = (tata << 1);
        if(h[fiu] > h[fiu ^ 1] && (fiu ^ 1) <= n)
            fiu ++;
        if(h[tata] > h[fiu]){
            int aux = h[tata];
            h[tata] = h[fiu];
            h[fiu] = aux;
            tata = fiu;
        } else break;
    }
}

std::vector<int> HeapSort::sort(){
    std::vector<int> v;
    for(; n ; ){
        v.push_back(get_min_heap());
        delete_heap();
    }
    return v;
}

/**************************** RadixSort ***************************/

class RadixSort{
private:
    int base;
    std::vector<int> a;
public:
    RadixSort(std::vector<int>&, int);
    std::vector<int> sort();
};

RadixSort::RadixSort(std::vector<int>& v, int base):a(v), base{base} {}

std::vector<int> RadixSort::sort(){
    std::vector<int> b(a.size(), 0); 
    for(int i = 0; i < 32; i += base){
        std::vector<int> fq((1<<base), 0);
        for(int j = 0; j < a.size(); ++ j)
            fq[(a[j] >> i) & ((1 << base) - 1)] ++;
        for(int j = 1; j < (1 << base); ++ j)
            fq[j] += fq[j - 1];
        for(int j = a.size() - 1; j >= 0; -- j){
            b[fq[(a[j] >> i) & ((1 << base) - 1)] - 1] = a[j];
            fq[(a[j] >> i) & ((1 << base) - 1)] --;
        }
        a = b;
    }
    return a;
}

/**************************** ShellSort ***************************/

class ShellSort{
private:
    std::vector<int>& a;
public:
    ShellSort(std::vector<int>&);
    std::vector<int> sort();
};

ShellSort::ShellSort(std::vector<int>& v): a(v){}

std::vector<int> ShellSort::sort(){
    for(int gap = a.size() / 2; gap > 0; gap /= 2)
        for(int i = gap; i < a.size(); ++ i){
            int temp = a[i];
            int j;
            for(j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];
            a[j] = temp;
        }
    return a;
}

/**************************** MergeSort ***************************/

class MergeSort{
private:
    std::vector <int> v;
public:
    MergeSort(std::vector<int>&);
    void merge(int, int, int);
    void merge_sort(int, int);
    std::vector<int> sort();
};

MergeSort::MergeSort(std::vector<int>& a): v(a){}

void MergeSort::merge(int st, int mij, int dr){
    int i;
    std::vector<int> a, b;
    for(i = mij; i >= st; -- i)
        a.push_back(v[i]);
    for(i = dr; i >= mij + 1; -- i)
        b.push_back(v[i]);
    i = st;
    while(a.size() > 0 && b.size() > 0){
        if(a[a.size() - 1] <= b[b.size() - 1]){
            v[i ++] = a[a.size() - 1];
            a.pop_back();
        } else {
            v[i ++] = b[b.size() - 1];
            b.pop_back();
        }
    }
    while(a.size()){
        v[i ++] = a[a.size() - 1];
        a.pop_back();
    }
    while(b.size()){
        v[i ++] = b[b.size() - 1];
        b.pop_back();
    }
}

void MergeSort::merge_sort(int st, int dr){
    if(st >= dr)
        return;
    int mij = st + (dr - st) / 2;
    merge_sort(st, mij);
    merge_sort(mij + 1, dr);
    merge(st, mij, dr);
}

std::vector<int> MergeSort::sort(){
    merge_sort(0, v.size() - 1);
    return v;
}

/**************************** QuickSort ***************************/

class QuickSort{
private:
    std::vector<int> a;
public:
    QuickSort(std::vector<int>&);
    int partition(int, int);
    void quick_sort(int, int);
    std::vector<int> sort();
};

QuickSort::QuickSort(std::vector<int>& v): a(v){}

int QuickSort::partition(int st, int dr){
    int pivot = a[dr];
    int i = st - 1;
    for(int j = st; j <= dr - 1;  ++ j)
        if(a[j] < pivot){
            ++ i;
            std::swap(a[i], a[j]);
        }
    std::swap(a[i + 1], a[dr]);
    return i + 1;
}

void QuickSort::quick_sort(int st, int dr){
    if(st >= dr)
        return;
    int pos = partition(st, dr);
    quick_sort(st, pos - 1);
    quick_sort(pos + 1, dr);
}

std::vector<int> QuickSort::sort(){
    quick_sort(0, a.size() - 1);
    return a;
}

/**************************** Teste ***************************/

class Teste{
private:
    std::vector<ii> t;
public:
    Teste();
    std::vector<int> generate_test(ii);
    bool check_sort(std::vector<int>&);
    void sorteaza();
};

Teste::Teste(){
    int n_max[] = {1000, 1000000, 100000000};
    int v_max[] = {1000, 1000000, 1000000000, 2000000000};
    for(int i = 0; i < 3; i ++)
        for(int j = 0; j < 4; j ++)
            t.push_back(std::make_pair(n_max[i], v_max[j]));
}

std::vector<int> Teste::generate_test(ii restr){
    int n_max = restr.first;
    int v_max = restr.second + 1;
    std::vector <int> v;

    for(int i = 0; i < n_max; ++ i)
        v.push_back(rand() % v_max);

    return v;
}

bool Teste::check_sort(std::vector<int>& v){
    for(int i = 0; i < v.size() - 1; i ++)
        if(v[i] > v[i + 1])
            return 0;
    return 1;
}

void Teste::sorteaza(){
    for(auto& restr: t){
        clock_t start_time, end_time;
        std::vector<int> v = generate_test(restr);
        RadixSort r{v, 8};
        HeapSort h{v};
        ShellSort s{v};
        MergeSort m{v};
        QuickSort q{v};

        std::cout << "N = " << restr.first << " MAX = " << restr.second << "\n";

        start_time = clock();
        v = r.sort();
        end_time = clock();
        if(check_sort(v))
            std::cout << "RadixSort: " << std::setprecision(6) << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n";
        else
            std::cout << "RadixSort gresit\n";

        start_time = clock();
        v = h.sort();
        end_time = clock();
        if(check_sort(v))
            std::cout << "HeapSort: " << std::setprecision(6) << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n";
        else
            std::cout << "HeapSort gresit\n";

        start_time = clock();
        v = s.sort();
        end_time = clock();
        if(check_sort(v))
            std::cout << "ShellSort: " << std::setprecision(6) << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n";
        else
            std::cout << "ShellSort gresit\n";

        start_time = clock();
        v = m.sort();
        end_time = clock();
        if(check_sort(v))
            std::cout << "MergeSort: " << std::setprecision(6) << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n";
        else
            std::cout << "MergeSort gresit\n";

        start_time = clock();
        v = q.sort();
        end_time = clock();
        if(check_sort(v))
            std::cout << "QuickSort: " << std::setprecision(6) << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n";
        else
            std::cout << "QuickSort gresit\n";

        std::cout << "\n";
    }
}

int main(){
    srand(time(NULL));

    Teste t;
    t.sorteaza();

    return 0;
}