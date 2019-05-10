function EER = PlotRoc(ClientScore,ImpostorScore,DistributionWeight)
% Author Denis
% Date June 27,2006
% Plot ROC similar to Adams's figure

if nargin<3
    DistributionWeight=1;
end


Bins = min(ClientScore):(max(ImpostorScore)-min(ClientScore))/10000:max(ImpostorScore);
ClientHist = hist(ClientScore,Bins);
ImpostorHist = hist(ImpostorScore,Bins);

for i=1:length(Bins)
    GAR(i) = sum(ClientHist(1:i))*100/sum(ClientHist);
    FAR(i) = sum(ImpostorHist(1:i))*100/sum(ImpostorHist);
end
Index = find(ClientScore<min(ImpostorScore)); 

GAR_1 = length(Index)*100/length(ClientScore);



% compute EER
Diff = abs((100-GAR)-FAR);
[minDiff,idx] = min(Diff);                 
% [(FAR(idx)+100-GAR(idx))/2, FAR(idx), 100-GAR(idx)]
EER = (FAR(idx)+100-GAR(idx))/2;
% d_prime = abs(mean(ImpostorScore)-mean(ClientScore))/sqrt(var(ImpostorScore)/2+var(ClientScore)/2);
% Dat = [(FAR(idx)+100-GAR(idx))/2,d_prime,GAR_1,Bins(idx)];

figure, semilogx(FAR,100-GAR);
% FAR_min = min(FAR); FAR_max = max(FAR);
% FRR_min = min(100-GAR); FRR_max = max(100-GAR);
% x = min([FAR_min,FRR_min]):0.0001:max([FAR_max,FRR_max]);
% hold on
% semilogx(x,x);
xlabel('FAR(%)')
ylabel('FRR(%)')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plot Distribution
if DistributionWeight==0
    Step = (max(ImpostorScore)-min(ClientScore))/10000;
    DistributionWeight = 1;
else
    Step = 0.005/DistributionWeight;
end

minScore = min([min(ClientScore),min(ImpostorScore)]);
maxScore = max([max(ClientScore),max(ImpostorScore)]);
X = 0:Step:maxScore+Step;
n = hist(ClientScore,X);
nfreq = n/sum(n)*100;
    
figure,plot(X*DistributionWeight,nfreq,'r-');
n = hist(ImpostorScore,X);
nfreq = n/sum(n)*100;
hold on
plot(X*DistributionWeight,nfreq,'g-.');
hold on
xlabel('Distance');
ylabel('Frequence(%)')
legend('Genuine user','Impostor');
