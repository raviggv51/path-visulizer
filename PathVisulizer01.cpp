#include<bits/stdc++.h>
using namespace std;
int sx,sy,dx,dy;
bool game=0;
vector<vector<int>>vis(25,vector<int>(50,-1));
vector<int>dir{0,1,0,-1,0}; 
queue<pair<int,int>>pq;
void setup()
{
	cout<<"Enter source co-ordinates in range of [25,50]"<<endl;
	cin>>sx>>sy;
	cout<<"Enter destination co-ordinates in range of [25,50]"<<endl;
	cin>>dx>>dy;
	vis[sx][sy]=0;
	pq.push({sx,sy});
}

void draw()
{
    system ("cls");
	for(int i=-1;i<=25;i++)
	{
		for(int j=-1;j<=50;j++)
		{
			if(i<0 ||j<0 || i==25 || j==50) cout<<'#';
			else if(i==sx && j==sy) cout<<'S';
			else if(i==dx && j==dy) cout<<'D';
			else if(vis[i][j]>0) cout<<"*";
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

int main()
{
	
	setup();
	while(!game)
	{
		draw();
		logic();
	}
	return 0;
}