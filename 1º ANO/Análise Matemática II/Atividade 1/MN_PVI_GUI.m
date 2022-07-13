%
% Dinis Meireles de Sousa Falcão, 2020130403
% David Seco Rodrigues, 2019130152
%
% MN_PVI_GUI  Métodos Numéricos para resolução de PVI com GUI
%   y'= f(t,y) com t=[a, b] e y(a)=y0 condição inicial
%
% INPUT:
%   f -> função do segundo membro de uma ED;
%   [a,b] -> extremos do intervalo de uma variável independente t;
%   n -> número de iterações do método;
%   t = a -> y = y0(condição inicial).
%   Método - {Euler, RK2, RK4}
% OUTPUT:
%   y - vector das aproximações discretas da solução exacta
%   Tabela das soluções aproximadas, solução exata e erros
%   Gráfico das aproximações e da solução exata
%


function varargout = MN_PVI_GUI(varargin)
% MN_PVI_GUI M-file for MN_PVI_GUI.fig
%      MN_PVI_GUI, by itself, creates a new MN_PVI_GUI or raises the existing
%      singleton*.
%
%      H = MN_PVI_GUI returns the handle to a new MN_PVI_GUI or the handle to
%      the existing singleton*.
%
%      MN_PVI_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MN_PVI_GUI.M with the given input arguments.
%
%      MN_PVI_GUI('Property','Value',...) creates a new MN_PVI_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before MN_PVI_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to MN_PVI_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help MN_PVI_GUI


% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @MN_PVI_GUI_OpeningFcn, ...
    'gui_OutputFcn',  @MN_PVI_GUI_OutputFcn, ...
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


% --- Executes just before MN_PVI_GUI is made visible.
function MN_PVI_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to MN_PVI_GUI (see VARARGIN)

% Choose default command line output for MN_PVI_GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes MN_PVI_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);

MyAtualizar(handles);


% --- Outputs from this function are returned to the command line.
function varargout = MN_PVI_GUI_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

function eF_Callback(hObject, eventdata, handles)
% hObject    handle to eF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eF as text
%        str2double(get(hObject,'String')) returns contents of eF as a double


% --- Executes during object creation, after setting all properties.
function eF_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function eA_Callback(hObject, eventdata, handles)
% hObject    handle to eA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eA as text
%        str2double(get(hObject,'String')) returns contents of eA as a double


% --- Executes during object creation, after setting all properties.
function eA_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function eB_Callback(hObject, eventdata, handles)
% hObject    handle to eB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eB as text
%        str2double(get(hObject,'String')) returns contents of eB as a double


% --- Executes during object creation, after setting all properties.
function eB_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function eN_Callback(hObject, eventdata, handles)
% hObject    handle to eN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eN as text
%        str2double(get(hObject,'String')) returns contents of eN as a double


% --- Executes during object creation, after setting all properties.
function eN_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function eY0_Callback(hObject, eventdata, handles)  
% hObject    handle to eY0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eY0 as text
%        str2double(get(hObject,'String')) returns contents of eY0 as a double


% --- Executes during object creation, after setting all properties.
function eY0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eY0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes when selected object is changed in bSelect.
function bSelect_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in bSelect
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)
MyAtualizar(handles);


% --- Executes on button press in bAtualizar.
function bAtualizar_Callback(hObject, eventdata, handles)
% hObject    handle to bAtualizar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
MyAtualizar(handles);


function MyAtualizar(handles)
% handles    structure with handles and user data (see GUIDATA)

strF = get(handles.eF,'String');
f    = @(t,y) eval(vectorize(strF));

try
    % Verifica se a função tem os parâmetros t e y
    syms t y; 
    fTeste=f(t,y);
catch me 
    errordlg('ERRO! Introduza uma função em t e y','ERRO', 'modal')
    return;
end
%Verifica se a é um numero real
a = str2num(get(handles.eA, 'String'));
if (~(isscalar(a))|| ~(isreal(a)))
    errordlg('Introduza um número real para "a"!','ERRO', 'modal')
    return;
end
%Verifica se b é um numero real e se é maior que a
b    = str2num(get(handles.eB, 'String'));
if (~(isscalar(b))|| ~(isreal(b)) || ~(b > a))
    errordlg('Introduza um número real para "b", com b > a','ERRO', 'modal')
    return;
end
%Verifica se n é um numero real e positivo
n    = str2num(get(handles.eN, 'String'));
if (~(isscalar(n) && isreal(n) && n>0))
    errordlg('Insira um número positivo para "n"!','ERRO', 'modal')
    return;
end
%Verifica se y0 é um numero real
y0   = str2num(get(handles.eY0,'String'));
if ~(isscalar(y0) && isreal(y0))
    errordlg('Introduza um número real para "y0"!','ERRO', 'modal')
    return;
end

escolha=find([handles.rEuler, ...
    handles.rEulerM, ...
    handles.rRK2, ...
    handles.rRK4, ...
    handles.rODE45, ...
    handles.rRK3, ...
    handles.rTodos] ==get(handles.bSelect,'SelectedObject'));
EULER = 1;
EULERM = 2;
Rk2   = 3;
Rk4   = 4;
Ode45 = 5;
Rk3 = 6;
TODOS = 7;

    sExata=dsolve(['Dy=', strF],...
                ['y(',num2str(a),')=',num2str(y0)]);
            g=@(t) eval(vectorize(char(sExata)));
            h=(b-a)/n;
            t=a:h:b;
            yExata=g(t);
            plot(t,yExata,'b')
            hold on
            legend ('Solução Exata')
    switch(escolha)
        case EULER
            yEuler = NEuler(f,a,b,n,y0); % chamada ao método de Euler
            
            plot(t,yEuler,'-r')
            legend('Solução Exata','Euler')
            set(handles.uiTabela,'ColumnName',[{'t'},{'Solução Exata'},...
                {'Euler'},{'Erro Euler'}]) %Nome das colunas
            yTab = [t.',yExata.', yEuler.',abs(yEuler-yExata).']; %apresentar resultados na tabela
            set(handles.uiTabela,'Data',num2cell(yTab))
        
        case EULERM
            yEulerM   = EulerM(f,a,b,n,y0);  % chamada ao método de Euler Melhorado
            
            plot(t,yEulerM,'-r')
            legend('Solução Exata','Euler Melhorado')
            set(handles.uiTabela,'ColumnName',[{'t'},{'Solução Exata'},...
                {'EulerM'},{'Erro EulerM'}]) %Nome das colunas
            yTab = [t.',yExata.', yEulerM.',abs(yEulerM-yExata).']; %apresentar resultados na tabela
            set(handles.uiTabela,'Data',num2cell(yTab))
        
        case Rk2
            yRk2 = RK2(f,a,b,n,y0);  % chamada ao método RK2
            plot(t,yRk2,'-r')
            hold off
            legend('Solução Exata','RK2');
            shg;
            
            yTab = [t.',yExata.',yRk2.',abs(yRk2-yExata).']; %apresentar resultados na tabela
            set(handles.uiTabela,'Data',num2cell(yTab)); %Nome das colunas
            set(handles.uiTabela,'ColumnName',[{'t'},{'Solução Exata'},... 
                {'RK2'},{'Erro RK2'}]);
            
        case Rk4
            yRk4 = RK4(f,a,b,n,y0);  % chamada ao método RK4
            plot(t,yRk4,'-r')
            hold off
            legend('Solução Exata','RK4');
            shg;
            
            yTab = [t.',yExata.',yRk4.',abs(yRk4-yExata).']; %apresentar resultados na tabela
            set(handles.uiTabela,'Data',num2cell(yTab));
            set(handles.uiTabela,'ColumnName',[{'t'},{'Solução Exata'},... 
                {'RK4'},{'Erro RK4'}]);%Nome das colunas
            
        case Ode45
            yOde45 = ODE45(f,a,b,n,y0); % chamada ao método Ode45
            plot(t,yOde45,'--r')
            hold off
            legend('Solução Exata','ODE45');
            shg;
           
            cTabela = [t.',yExata.',yOde45,abs(yOde45.'-yExata).']; %apresentar resultados na tabela
            set(handles.uiTabela,'Data',num2cell(cTabela));
            set(handles.uiTabela,'ColumnName',[{'t'},{'Solução Exata'},... 
                {'ODE45'},{'Erro ODE45'}]); %Nome das colunas
            
        case Rk3
            yRk3 = RK3(f,a,b,n,y0);  % chamada ao método RK3
            plot(t,yRk3,'-r')
            hold off
            legend('Solução Exata','RK3');
            shg;
            
            yTab = [t.',yExata.',yRk3.',abs(yRk3-yExata).']; %apresentar resultados na tabela
            set(handles.uiTabela,'Data',num2cell(yTab));
            set(handles.uiTabela,'ColumnName',[{'t'},{'Solução Exata'},... 
                {'RK3'},{'Erro RK3'}]); %Nome das colunas
        case TODOS
            [t,y] = MetodosNum(f,a,b,n,y0);  % chamada todos os métodos
      
        % apresentar os dados no grafico
        hold on
        legend('EXATA','EULER','EULER_M','RK2','RK4','ODE45','RK3');
        %apresentar resultados na tabela
       yTab = table(t.', yExata.', y(:,1), abs(y(:,1)-yExata.'),y(:,2),abs(y(:,2)-yExata.'), y(:,3),abs(y(:,3)-yExata.'), y(:,4), abs(y(:,4)-yExata.'), y(:,5),abs(y(:,5)-yExata.'),y(:,6) , abs(y(:,6)-yExata.'));
       set(handles.uiTabela,'Data',table2cell(yTab));
       set(handles.uiTabela,'ColumnName',[{'t'},{'Exata'},{'Euler'},{'Erro_Euler'},{'Euler_M'},{'Erro_Euler_M'},{'RK2'},{'Erro_RK2'},{'RK4'},{'Erro_RK4'},{'ODE45'},{'Erro_ODE45'},{'RK3'},{'Erro_RK3'}]); %Nome das colunas
       
    end
    grid on
    xlabel('t')
    ylabel('y')
    hold off

