clear

format compact

% 1. Generate X1
l=2; %Dimensionality
poi_per_square=30; %Points per square
N=9*poi_per_square; %Total no. of points
rand('seed',0)
X1=[];
y1=[];
for i=0:2
    for j=0:2
        X1=[X1 rand(l,poi_per_square)+...
            [i j]'*ones(1,poi_per_square)];
        if(mod(i+j,2)==0)
            y1=[y1 ones(1,poi_per_square)];
        else
            y1=[y1 -ones(1,poi_per_square)];
        end
    end
end

% Generate X2
rand('seed',100)
X2=[];
y2=[];
for i=0:2
    for j=0:2
        X2=[X2 rand(l,poi_per_square)+...
            [i j]'*ones(1,poi_per_square)];
        if(mod(i+j,2)==0)
            y2=[y2 ones(1,poi_per_square)];
        else
            y2=[y2 -ones(1,poi_per_square)];
        end
    end
end

dlmwrite('data252/data252.mat', X1);
dlmwrite('data252/data252.mat', y1, '-append');
dlmwrite('data252/data252-test.mat', X2);
dlmwrite('data252/data252-test.mat', y2, '-append');

