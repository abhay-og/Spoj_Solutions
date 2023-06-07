#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set=tree<T,null_type, less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>
using ordered_multiset=tree<T,null_type,less_equal<T>,rb_tree_tag, tree_order_statistics_node_update>;
#define setbits(x) __builtin_popcountll(x)
#define binstr(n,x) bitset<n>(x).to_string()
#define lzs(x) __builtin_clzll(x)
#define tzs(x) __builtin_ctzll(x)
#define msb(x) __lg(x)
#define lsb(x) __builtin_ffsll(x)-1
using ll=long long;
using ld=long double;
const int MOD=1e9+7;
const ll INF=1e18;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand_ll(ll l=0, ll r=1e18){uniform_int_distribution<ll> uid(l,r);return uid(rng);}
const int N=5e5+1;

void solve(){
    int n;
    ll ans=0;
    cin>>n;
    vector<bitset<N>> v(10);
    bitset<N> b;
    for(ll i=0,x;i<n;i++){
        cin>>x;
        string s=to_string(x);
        sort(s.begin(),s.end());
        s.resize(unique(s.begin(),s.end())-s.begin());
        for(auto &z:s)v[z-'0'][i]=1;
    }
    for(ll msk=1;msk<1024;msk++){
        int sb=setbits(msk);
        b.set();
        for(int i=0;i<10;i++){
            if(msk&(1ll<<i))b&=v[i];
        }
        ll cnt=b.count();
        if(sb&1)ans+=(cnt*(cnt-1))/2;
        else ans-=(cnt*(cnt-1))/2;
    }
    cout<<ans<<'\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t=1;
    // cin>>t;
    for (int i=1;i<=t;i++){
        // cout<<"Case #"<<i<<' ';
        solve();
    }
    return 0;
}
