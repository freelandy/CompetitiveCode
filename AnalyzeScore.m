function eer=AnalyzeScore()
% Author Denis
% Date July 19, 2007
% Analyze score from similarity.sim

% picfolder = 'h:\fusion\test\'; 

logname = 'log.txt';
fid = fopen(logname);
picperpalm = fscanf(fid, '%d,%d', [2 inf]);    % It has two rows now.
picperpalm = picperpalm';
picperpalm = picperpalm(:,2);
PicNum=sum(picperpalm);
PalmNum = size(picperpalm,1);
fclose(fid);

ClientIndex = zeros(PicNum,2);
ImpostorIndex = zeros(PicNum,2);
picidx = 0;
for i=1:PalmNum
	for j=1:picperpalm(i)
        picidx = picidx+1;
        ClientIndex(sum(picperpalm(1:i-1))+j,1) = sum(picperpalm(1:i-1))+j+1;
        ClientIndex(sum(picperpalm(1:i-1))+j,2) = sum(picperpalm(1:i-1))+picperpalm(i);
        ImpostorIndex(sum(picperpalm(1:i-1))+j,1) = sum(picperpalm(1:i-1))+picperpalm(i)+1;
        ImpostorIndex(sum(picperpalm(1:i-1))+j,2) = PicNum;
    end
end
ClientScore = zeros(sum(ClientIndex(:,2)-ClientIndex(:,1)+1),1);
ImpostorScore = zeros(sum(ImpostorIndex(:,2)-ImpostorIndex(:,1)+1),1);
minImpostor = ones(PicNum,2);
maxClient = ones(PicNum,2);

fid = fopen('similarity.sim','rb');

for i=1:PicNum    
    F = fread(fid, PicNum,'float32')';  
    % F = score(:,i);
    ClientScore(sum(ClientIndex(1:i-1,2)-ClientIndex(1:i-1,1)+1)+1:sum(ClientIndex(1:i,2)-ClientIndex(1:i,1)+1)) = F(ClientIndex(i,1):ClientIndex(i,2));
    ImpostorScore(sum(ImpostorIndex(1:i-1,2)-ImpostorIndex(1:i-1,1)+1)+1:sum(ImpostorIndex(1:i,2)-ImpostorIndex(1:i,1)+1)) = F(ImpostorIndex(i,1):ImpostorIndex(i,2));    
    if ImpostorIndex(i,2)-ImpostorIndex(i,1)>=0
        [minImpostor(i,1),idx] = min(F(ImpostorIndex(i,1):ImpostorIndex(i,2)));
        minImpostor(i,2) = idx+ImpostorIndex(i,1)-1;
    end
    if ClientIndex(i,2)-ClientIndex(i,1)>=0
        [maxClient(i,1),idx] = max(F(ClientIndex(i,1):ClientIndex(i,2)));
        maxClient(i,2) = idx+ClientIndex(i,1)-1;
    end
end
fclose(fid);

ClientScore(ClientScore>0.39) = ClientScore(ClientScore>0.39)-0.1;


eer=PlotRoc(ClientScore,ImpostorScore);


