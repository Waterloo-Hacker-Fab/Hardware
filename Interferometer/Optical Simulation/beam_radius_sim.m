%% This is a script for visualizing the beam radius at different z lenghts.
% The VLM-520-60 LPO laser was choosen for the following reasons: 
% 1. Green laser (lower wavelength -> can measure smaller displacements)
% 2. Comes with aspherical glass lens already installed (produces circular beam shape, no need for extra optics)
% 3. Possible downside: the spot size is too small (< 1mm at dist of 0-50cm)

%% Parameters
% We will be using the VLM-520-60 LPO laser for the parameters

lambda = (515e-9+530e-9)/2;      % wavelength [m]
output_aperture = 6e-4; % Taken from datasheet (0.6mm)

w0x = 1e-3;        % waist radius x [m]
w0y = 1e-3;        % waist radius y [m] (set different for ellipse)

w0x = output_aperture/2;        % waist radius x [m]
w0y = output_aperture/2;        % waist radius y [m] (set different for ellipse)

zMax = 0.2;        % max distance to plot [m]
Npoints = 500;     % resolution for plotting
Nz = 20;           % number of cross-sections to show

% Calculate rayleight range in X & Y
zRx = (pi * w0x^2) / lambda;
zRy = (pi * w0y^2) / lambda;

z = linspace(0, zMax, Npoints);

% Gaussian beam radius at dist z
wx = w0x .* sqrt(1 + (z ./ zRx).^2);
wy = w0y .* sqrt(1 + (z ./ zRy).^2);

%% Plot Beam Radius vs z
figure;
plot(z*1e3, wx*1e6, 'r', 'LineWidth', 2); hold on;
plot(z*1e3, wy*1e6, 'b--', 'LineWidth', 2);
xlabel('Distance z [mm]');
ylabel('Beam radius w(z) [um]');
legend('w_x(z)', 'w_y(z)');
title('Gaussian Beam Radius vs Propagation Distance (Circular Beam Shape)');
grid on;


%% Stacked intensity cross-sections
% Define grid
x = linspace(-2*w0x, 2*w0x, 200);
y = linspace(-2*w0y, 2*w0y, 200);
[X, Y] = meshgrid(x,y);

zSlices = linspace(0, zMax, Nz);

figure;
hold on;
for i = 1:Nz
    zi = zSlices(i);
    wxi = w0x * sqrt(1 + (zi/zRx)^2);
    wyi = w0y * sqrt(1 + (zi/zRy)^2);
    
    % Normalized Gaussian intensity
    I = exp(-2*(X.^2./wxi.^2 + Y.^2./wyi.^2));
    
    % Plot as a surface offset along z
    surf(X*1e3, Y*1e3, zi*ones(size(I)), I, 'EdgeColor','none');
end
xlabel('x [mm]');
ylabel('y [mm]');
zlabel('z [m]');
title('Stacked Gaussian Beam Cross-Sections');
colormap hot;
shading interp;
view(45,30);