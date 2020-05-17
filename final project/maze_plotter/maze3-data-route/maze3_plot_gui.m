function varargout = maze3_plot_gui(varargin)
% maze3_plot_gui MATLAB code for maze3_plot_gui.fig
%      maze3_plot_gui, by itself, creates a new maze3_plot_gui or raises the existing
%      singleton*.
%
%      H = maze3_plot_gui returns the handle to a new maze3_plot_gui or the handle to
%      the existing singleton*.
%
%      maze3_plot_gui('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in maze3_plot_gui.M with the given input arguments.
%
%      maze3_plot_gui('Property','Value',...) creates a new maze3_plot_gui or raises
%      the existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before maze3_plot_gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to maze3_plot_gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help maze3_plot_gui

% Last Modified by GUIDE v2.5 03-Jan-2019 02:21:35

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @maze3_plot_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @maze3_plot_gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

% --- Executes just before maze3_plot_gui is made visible.
function maze3_plot_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to maze3_plot_gui (see VARARGIN)

% Choose default command line output for maze3_plot_gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

initialize_gui(hObject, handles, false);

% UIWAIT makes maze3_plot_gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = maze3_plot_gui_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes during object creation, after setting all properties.
function initialize_gui(fig_handle, handles, isreset)
% If the maze field is present and the Export flag is false, it means
% we are we are just re-initializing a GUI by calling it from the cmd line
% while it is up. So, bail out as we dont want to Export the data.
if isfield(handles, 'maze') && ~isreset
    return;
end

% Update handles structure
%guidata(handles.figure1, handles);


% --- Executes on button press in load_map.
function load_map_Callback(hObject, eventdata, handles)
% hObject    handle to load_map (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[map,in_out,col,row,height]=load_map();
handles.maze.col=col;
handles.maze.row=row;
handles.maze.height=height;
handles.maze.map=map;
handles.maze.in_out=in_out;
guidata(hObject,handles)

%figure(handles.maze.figure);
ax0=plot_maze3(map,'wall'); axis equal;
handles.maze.ax0=ax0;
guidata(hObject,handles);
plot3(ax0,in_out(1),in_out(2),in_out(3),'kx',in_out(4),in_out(5),in_out(6),'k^','markersize',8);
grid on;
function [map,in_out,col,row,height]=load_map()
[FILENAME, PATHNAME, FILTERINDEX] = uigetfile('*.txt', 'Pick a map file in txt.')
fid=fopen([PATHNAME '/' FILENAME],'r');
[map,count]=fscanf(fid,'%d,%d,%d,%d,%d,%d,%d,%d,%d');
map=reshape(map,[9,count/9]); map=map.';
fclose(fid);
col=max(max(map(:,1))); 
row=max(max(map(:,2))); 
height=max(max(map(:,3)));

[FILENAME, PATHNAME, FILTERINDEX] = uigetfile('*.txt', 'Start and Destination point file in txt.')
fid=fopen([PATHNAME '/' FILENAME],'r');
%[in_out,count]=fscanf(fid,'%d,%d,%d,%d,%d,%d');
[index,count]=fscanf(fid,'%d,');
y=mod(index,row); y(y==0)=row;
x=mod((index-y)/row,col)+1;
z=(index-y-(x-1)*row)/col/row+1;
in_out=[x(1) y(1) z(1) x(2) y(2) z(2)];
fclose(fid);

 
% --- Executes on button press in load_route.
function load_route_Callback(hObject, eventdata, handles)
% hObject    handle to load_route (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[FILENAME, PATHNAME, FILTERINDEX] = uigetfile('*.txt', 'Pick a route file in txt.');
% fid=fopen('maze3_route.txt','r');
% [xyz,count]=fscanf(fid,'%d,%d,%d');
% fclose(fid);
% figure(handles.maze.figure);
% xyz=reshape(xyz,[3,count/3]);xyz=xyz.';
% plot3(xyz(:,1),xyz(:,2),xyz(:,3),'b--','linewidth',2);
fid=fopen([PATHNAME '/' FILENAME],'r');
[index,count]=fscanf(fid,'%d,')
%z=(index-mod(index,row*col))/row*col+1;
col=handles.maze.col;
row=handles.maze.row;
height=handles.maze.height;

y=mod(index,row); y(y==0)=row;
x=mod((index-y)/row,col)+1;
z=(index-y-(x-1)*row)/row/col+1;
fclose(fid);
plot3(handles.maze.ax0,x,y,z,'b--','linewidth',2);

function ax=plot_maze3(map,opt)
figure;
%map=[x(:),y(:),visited(:),wN(:),wS(:),wE(:),wW(:)];
ax=axes;
set(ax,'nextplot','add');
if strcmp(opt,'wall')
for ii=1:size(map,1)
    x=map(ii,1); y=map(ii,2); z=map(ii,3);
  % [x,y]=ind2sub(ii,[row,col]);
      for jj=1:6
        if map(ii,jj+3)>0
            switch jj
                case 1
                    fill3([x-0.5 x+0.5 x+0.5 x-0.5 x-0.5],[y+0.5 y+0.5 y+0.5 y+0.5 y+0.5],[z-0.5 z-0.5 z+0.5 z+0.5 z-0.5], 'r','facealpha',0.3);
               %      plot3([x-0.5 x+0.5],[y+0.5 y+0.5],[z z], 'r','linewidth',2);
                case 2
                    fill3([x-0.5 x+0.5 x+0.5 x-0.5 x-0.5],[y-0.5 y-0.5 y-0.5 y-0.5 y-0.5],[z-0.5 z-0.5 z+0.5 z+0.5 z-0.5], 'r','facealpha',0.3);
                  %   plot3([x-0.5 x+0.5],[y-0.5 y-0.5],[z z], 'r','linewidth',2);
        
                case 3
                    fill3([x+0.5 x+0.5 x+0.5 x+0.5 x+0.5],[y-0.5 y+0.5 y+0.5 y-0.5 y-0.5],[z-0.5 z-0.5 z+0.5 z+0.5 z-0.5], 'r','facealpha',0.3);
               %      plot3([x+0.5 x+0.5],[y-0.5 y+0.5],[z z], 'r','linewidth',2);

                case 4
                    fill3([x-0.5 x-0.5 x-0.5 x-0.5 x-0.5],[y-0.5 y+0.5 y+0.5 y-0.5 y-0.5],[z-0.5 z-0.5 z+0.5 z+0.5 z-0.5], 'r','facealpha',0.3);
                    % plot3([x-0.5 x-0.5],[y-0.5 y+0.5],[z z], 'r','linewidth',2);
                case 5
                   %  plot3([x+0.5 x-0.5],[y+0.5 y-0.5],[z+0.5 z+0.5], 'r','linewidth',2);
                    fill3([x-0.5 x+0.5 x+0.5 x-0.5 x-0.5],[y-0.5 y-0.5 y+0.5 y+0.5 y-0.5],[z+0.5 z+0.5 z+0.5 z+0.5 z+0.5], 'g','facealpha',0.3);
                case 6
                   %  plot3([x+0.5 x-0.5],[y-0.5 y+0.5],[z-0.5 z-0.5], 'r','linewidth',2);
                   fill3([x-0.5 x+0.5 x+0.5 x-0.5 x-0.5],[y-0.5 y-0.5 y+0.5 y+0.5 y-0.5],[z-0.5 z-0.5 z-0.5 z-0.5 z-0.5], 'g','facealpha',0.3);
                otherwise
            end
        end
        
    end
  end
  
end
%%

