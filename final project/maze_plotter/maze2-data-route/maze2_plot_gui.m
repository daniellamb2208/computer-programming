function varargout = maze2_plot_gui(varargin)
%MAZE2_PLOT_GUI MATLAB code file for maze2_plot_gui.fig
%      MAZE2_PLOT_GUI, by itself, creates a new MAZE2_PLOT_GUI or raises the existing
%      singleton*.
%
%      H = MAZE2_PLOT_GUI returns the handle to a new MAZE2_PLOT_GUI or the handle to
%      the existing singleton*.
%
%      MAZE2_PLOT_GUI('Property','Value',...) creates a new MAZE2_PLOT_GUI using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to maze2_plot_gui_OpeningFcn.  This calling syntax produces a
%      warning when there is an existing singleton*.
%
%      MAZE2_PLOT_GUI('CALLBACK') and MAZE2_PLOT_GUI('CALLBACK',hObject,...) call the
%      local function named CALLBACK in MAZE2_PLOT_GUI.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help maze2_plot_gui

% Last Modified by GUIDE v2.5 26-Dec-2019 13:19:40

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @maze2_plot_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @maze2_plot_gui_OutputFcn, ...
                   'gui_LayoutFcn',  [], ...
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


% --- Executes just before maze2_plot_gui is made visible.
function maze2_plot_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for maze2_plot_gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes maze2_plot_gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = maze2_plot_gui_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;




% --- Executes on button press in load_route.
function load_route_Callback(hObject, eventdata, handles)
% hObject    handle to load_route (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[FILENAME, PATHNAME, FILTERINDEX] = uigetfile('*.txt', 'Pick a route file in txt.')
fid=fopen([PATHNAME '/' FILENAME],'r');
[index,count]=fscanf(fid,'%d,')
fclose(fid);
row=handles.maze.row;
col=handles.maze.col;
y=mod(index,row);
y(y==0)=row;
x=(index-y)/row+1;
%plot(handles.ax1,x,y,'r--','linewidth',2);
plot(handles.ax2,x,y,'r--','linewidth',2);
%cla(handles.ax1);


% --- Executes on button press in load_map.
function load_map_Callback(hObject, eventdata, handles)
% hObject    handle to load_map (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[map, in_out,row,col]=load_map();
handles.maze.map=map;
handles.maze.in_out=in_out;
handles.maze.row=row;
 handles.maze.col=col;
guidata(hObject,handles);
f=figure;
ax2=axes('parent',f);
set(ax2,'nextplot','add');
plot_maze(ax2,map,in_out);axis equal;
handles.ax2=ax2;
guidata(hObject,handles);

%% ------------------------ load maze ----------------------

function [map,in_out,row,col]=load_map()
[FILENAME, PATHNAME, FILTERINDEX] = uigetfile('*.txt', 'Pick a map file in txt.')
fid=fopen([PATHNAME '/' FILENAME],'r');
[map,count]=fscanf(fid,'%d,%d,%d,%d,%d,%d');
map=reshape(map,[6,count/6]); map=map.';
fclose(fid);
[FILENAME, PATHNAME, FILTERINDEX] = uigetfile('*.txt', 'Pick a input and out location.')

fid=fopen([PATHNAME '/' FILENAME],'r');
[in_out,count]=fscanf(fid,'%d,%d');

fclose(fid);
col=max(max(map(:,1)))
row=max(max(map(:,2)))

 y=mod(in_out,row);
 y(y==0)=row;
 x=(in_out-y)/row+1;
 in_out=[x(1);y(1);x(2);y(2)]
 


%% ------------------------ plot maze ----------------------
function plot_maze(ax1,map,in_out)
%map=[x(:),y(:),visited(:),wN(:),wS(:),wE(:),wW(:)];
%plot(ax1,[],[]);
siz=[1 1];
set(ax1,'nextplot','add');
for ii=1:size(map,1)
    x=map(ii,1);
    y=map(ii,2);
    text(x,y,num2str(ii));
    for jj=1:4
        if map(ii,jj+2)>0
            switch jj
                case 1
                    plot([x-0.5 x+0.5],[y+0.5 y+0.5],'b-','linewidth',2);
                case 2
                    plot([x-0.5 x+0.5],[y-0.5 y-0.5],'b-','linewidth',2);
                case 3
                    plot([x+0.5 x+0.5],[y-0.5 y+0.5],'b-','linewidth',2);
                case 4
                    plot([x-0.5 x-0.5],[y-0.5 y+0.5],'b-','linewidth',2);
                otherwise
            end
        end
        
    end
end
 plot(ax1,in_out(1),in_out(2),'kx',in_out(3),in_out(4),'k^','markersize',8);
 set(ax1,'visible','off');
 %set(ax1,'xlim',[0 col+1],'ylim',[0 row+1],'visible','off');
