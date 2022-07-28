#include<bits/stdc++.h>
using namespace std;
int sx,sy,dx,dy;
bool game=0,stop=0;
vector<vector<int>>vis(25,vector<int>(50,-1));
vector<int>dir{0,1,0,-1,0}; 
queue<pair<int,int>>pq;

void wall()
{
	int i=0,j=0;
	for(i=12,j=3;j<=45;j++)
	vis[i][j]=INT_MIN;
	i=2;j=25;
	for(;i<=22;i++)
	vis[i][j]=INT_MIN;
	i= 10;
	for(j =3;j<45;j++)
	vis[i][j]=INT_MIN;
	j= 9;
	for(i=7;i<22;i++)
	vis[i][j]=INT_MIN;
	i=3,j=45;
	while(1)
	{
	    vis[i++][j--]=INT_MIN;
	    if(i==22 ) break;
	}
}

void setup()
{
	while(1){
	cout<<"Enter source co-ordinates in range of [25,50]"<<endl;
	cin>>sx>>sy;
		if(vis[sx][sy]==INT_MIN)
		{
			cout<<"Wall is present at this position"<<endl;
			//cin>>sx>>sy;
		}
		else break;
		
	}
	while(1)
	{
		cout<<"Enter destination co-ordinates in range of [25,50]"<<endl;
		cin>>dx>>dy;
		if(vis[dx][dy]==INT_MIN)
		{
			cout<<"Wall is present at this position"<<endl;
		//	cin>>sx>>sy;	
		}
		else{
			vis[sx][sy]=0;
			pq.push({sx,sy});
			break;
		}
	}
}

void draw()
{
	for(int i=-1;i<=25;i++)
	{
		for(int j=-1;j<=50;j++)
		{
			if(i<0 ||j<0 || i==25 || j==50) cout<<'#';
			else if(i==sx && j==sy) cout<<'S';
			else if(i==dx && j==dy) cout<<'D';
			else if(vis[i][j]>0) cout<<".";
			else if(vis[i][j]==INT_MIN) cout<<"\\";
			else cout<<" ";
		}
		cout<<endl;
	}
}

bool isvalid(int x,int y,vector<vector<int>>& vis)
{
	if(x<0 || y<0 || x>=25 || y>=50 || vis[x][y]>0) return 0;
	return 1;
}

void logic()
{
	pair<int,int>top=pq.front();
	int cx=top.first,cy=top.second;
	pq.pop();
	if(cx==dx && cy==dy){
		game=1;
		return;
	}
	for(int i=0;i<4;i++)
	{
		int x=cx+dir[i],y=cy+dir[i+1];
		if(isvalid(x,y,vis) && vis[x][y]==-1)
		{
			vis[x][y]=vis[cx][cy]+1;
			pq.push({x,y});
		}
	}
}

void dfs(int i,int j,vector<vector<int>>&vis,int x)
{
	if(i<0 || j<0|| i>=25 || j>=50 || x<vis[i][j] || stop || vis[i][j]==-1 || vis[i][j]==INT_MIN) return;
	x=vis[i][j];
	if(sx==i && sy==j)
	{
		stop=1;
		return ;
	}
	vis[i][j]=INT_MAX;
	dfs(i+1,j,vis,x);
	dfs(i,j+1,vis,x);
	dfs(i-1,j,vis,x);
	dfs(i,j-1,vis,x);
}

void filter()
{
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<50;j++)
		{
			if(vis[i][j]==INT_MAX) vis[i][j]=1;
			else if(vis[i][j]==INT_MIN) continue;
			else vis[i][j]=0;
		}
	}
}

int main()
{
	wall();
	setup();
	while(!game)
	{
		draw();
		logic();
	}
	cout<<endl;
	cout<<"Distance from source to destination is "<<vis[dx][dy]<<endl;
	dfs(dx,dy,vis,vis[dx][dy]);
	filter();
	draw();
	return 0;
}