function [Z, fig] = BetterSpecAnal(img)
	W = hamming(64) * hamming(64)';
	N = 64;		
    other=size(img);
	w_start = floor((size(img) - 5*N)/2);
	X = double(img);

	Z = zeros(N, N);
	for i = 1:5
		for j = 1:5
            thing1=w_start(1) + (i-1)*N:w_start(1) + i*N - 1;
            thing2=w_start(2) + (j-1)*N:w_start(2) + j*N - 1
			z = X(w_start(1) + (i-1)*N:w_start(1) + i*N - 1, w_start(2) + (j-1)*N:w_start(2) + j*N - 1);
            int1=fft2(z.*W);
            int2=fftshift(int1);
            int3=int2.^2;
            int4=abs(int3)*(1/N^2);
            int5=log(int4);
            
			Z = Z + log((1/N^2)*abs(fftshift(fft2(z.*W)).^2));
		end
	end

	Z = Z/25;
	 
	x = 2*pi*((0:(N-1)) - N/2)/N;
	y = 2*pi*((0:(N-1)) - N/2)/N;
	fig = figure; 
	mesh(x,y,Z);
	xlabel('\mu');
	ylabel('\nu');
end