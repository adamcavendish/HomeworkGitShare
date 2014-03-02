close('all');
clear

% 1. To generate the first 400 points of X 
randn('seed',0)
m=[0 0; 10 0; 0 9; 9 8];
S(:,:,1)=eye(2);
S(:,:,2)=[1.0 .2; .2 1.5];
S(:,:,3)=[1.0 .4; .4 1.1];
S(:,:,4)=[.3 .2; .2 .5];
n_points=100*ones(1,4); 
X=[];
for i=1:4
    X=[X; mvnrnd(m(i,:),S(:,:,i),n_points(i))];
end
X=X';

% Generate the remaining 100 points
noise=rand(2,100)*14-2;
X=[X noise];

% Plot the data set
figure(1), plot(X(1,:),X(2,:),'.b')
figure(1), axis equal

% To apply the k-means algorithm  
m=4;
[l,N]=size(X);
rand('seed',0)
center_ini=rand(l,m);
[center,label]=k_means(X,center_ini);

% Plot the clusters
figure(2), hold on
figure(2), plot(X(1,label==1),X(2,label==1),'r.',...
X(1,label==2),X(2,label==2),'g*',X(1,label==3),X(2,label==3),'bo',...
X(1,label==4),X(2,label==4),'cx',X(1,label==5),X(2,label==5),'md',...
X(1,label==6),X(2,label==6),'yp',X(1,label==7),X(2,label==7),'ks')
figure(2), plot(center(1,:),center(2,:),'k+')
figure(2), axis equal

