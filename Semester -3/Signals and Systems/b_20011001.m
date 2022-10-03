clc; clear all; close all;
hataPayi = 10; %karşılaştırma için tanımlandı
secim = input("tel.wav için 1, 11 haneli oluşturulmuş ses için 2 giriniz.\n");
if secim == 1;
    [tel,fs] = audioread('tel.wav');
    n=7;
elseif secim == 2;
    [tel,fs] = audioread('20011001.wav');
    n=11;
else
    disp("Geçersiz değer.");
end
T = 1/fs;
t = (0:T:length(tel)*T - T);
%sound(tel);
figure(1);
stem(t,tel);
figure(2);
plot(t,tel);

d = floor(length(tel)/n);
for i = 0:n-1;
    tus = tel(i*d+1:(i+1)*d);
    tmp = fft(tus);
    P2 = abs(tmp/d);
    P1 = P2(1:d/2+1);
    P1 = 2*P1;
    f = fs*(0:(d/2))/d;
        %rapor için
        %figure(i+1);
        %plot(f,P1);
        %title([num2str(i+1),'. tuşun frekans spektrumu']);
    %2 pik noktasının hesaplanması
    max = 1;
    max2 = max;
    len = length(P1);
    for j = 2:len;
        if P1(max) < P1(j)
            max2 = max;
            max = j;
        elseif P1(max2) < P1(j)
            max2 = j;
        end
    end
    if max2 < max;
        tmp = max;
        max = max2;
        max2 = tmp;
    end
    max = max*fs/d;
    max2 = max2*fs/d;
    %tuşları yazdırma
    if max < 697 + hataPayi;
        if max2 < 1209 + hataPayi;
            disp([num2str(i+1),'. tus: 1']);
        elseif max2 < 1336 + hataPayi;
            disp([num2str(i+1),'. tus: 2']);
        else max2 < 1477 + hataPayi;
            disp([num2str(i+1),'. tus: 3']);
        end
    elseif max < 770 + hataPayi;
        if max2 < 1209 + hataPayi;
            disp([num2str(i+1),'. tus: 4']);
        elseif max2 < 1336 + hataPayi;
            disp([num2str(i+1),'. tus: 5']);
        else max2 < 1477 + hataPayi;
            disp([num2str(i+1),'. tus: 6']);
        end
    elseif max < 852 + hataPayi;
        if max2 < 1209 + hataPayi;
            disp([num2str(i+1),'. tus: 7']);
        elseif max2 < 1336 + hataPayi;
            disp([num2str(i+1),'. tus: 8']);
        else max2 < 1477 + hataPayi;
            disp([num2str(i+1),'. tus: 9']);
        end
    elseif max < 941 + hataPayi;
        if max2 < 1209 + hataPayi;
            disp([num2str(i+1),'. tus: *']);
        elseif max2 < 1336 + hataPayi;
            disp([num2str(i+1),'. tus: 0']);
        else max2 < 1477 + hataPayi;
            disp([num2str(i+1),'. tus: #']);
        end
    end
end