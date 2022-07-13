%Atividade 3
%Dinis Meireles de Sousa Falcão - 2020130403
%David Seco Rodrigues - 2019130152
%
% IntegracaoNumerica Integração Numérica
% Máquina para calcular soluções aproximadas de derivadas
%


function varargout = IntegracaoNumerica(varargin)
% INTEGRACAONUMERICA M-file for IntegracaoNumerica.fig
%      INTEGRACAONUMERICA, by itself, creates a new INTEGRACAONUMERICA or raises the existing
%      singleton*.
%
%      H = INTEGRACAONUMERICA returns the handle to a new INTEGRACAONUMERICA or the handle to
%      the existing singleton*.
%
%      INTEGRACAONUMERICA('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in INTEGRACAONUMERICA.M with the given input arguments.
%
%      INTEGRACAONUMERICA('Property','Value',...) creates a new INTEGRACAONUMERICA or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before IntegracaoNumerica_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to IntegracaoNumerica_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help IntegracaoNumerica


% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @IntegracaoNumerica_OpeningFcn, ...
                   'gui_OutputFcn',  @IntegracaoNumerica_OutputFcn, ...
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


% --- Executes just before IntegracaoNumerica is made visible.
function IntegracaoNumerica_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to IntegracaoNumerica (see VARARGIN)

% Choose default command line output for IntegracaoNumerica
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes IntegracaoNumerica wait for user response (see UIRESUME)
% uiwait(handles.figureIntegracaoNumerica);
MyAtualizar(handles);


% --- Outputs from this function are returned to the command line.
function varargout = IntegracaoNumerica_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pbAtualiza.
function pbAtualiza_Callback(hObject, eventdata, handles)
% hObject    handle to pbAtualiza (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
MyAtualizar(handles);


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


% --- Executes during object creation, after setting all properties.
function pbGrafico_CreateFcn(hObject, eventdata, handles)
% hObject    handle to pbGrafico (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes when user attempts to close figureIntegracaoNumerica.
function figureIntegracaoNumerica_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figureIntegracaoNumerica (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure
%delete(hObject);
set(hObject,'Visible','Off');

% --- Função auxiliar associada ao botão Atualizar.
function MyAtualizar(handles)
% handles estrutura de dados com as handles para os objetos...
syms x;
strF=get(handles. tFuncao,'String');
f=@(x) eval(vectorize(char(strF)));
df=diff(f(x));
dfdx=@(x) eval(vectorize(char(df)));

a=str2num(get(handles.eA,'String'));
b=str2num(get(handles.eB,'String'));
n=str2num(get(handles.eN,'String'));

testeAReal=MException('MATLAB:MyAtualizar:badAReal','Introduza um número real em "a"!');
testeBReal=MException('MATLAB:MyAtualizar:badBReal','Introduza um número real em "b"!');
testeBA=MException('MATLAB:MyAtualizar:badBA','Introduza em "a" um número inferior a "b"!');
testeNInteiro=MException('MATLAB:MyAtualizar:badNInteiro','Introduza um número inteiro positivo em "n"!');

try
	if ~(isscalar(a)&&isreal(a))
		set(handles.eA,'BackgroundColor',[1 0.65 0.65]);
		throw(testeAReal);
	else
		set(handles.eA,'BackgroundColor','white');
		
		if ~(isscalar(b)&&isreal(b))
			set(handles.eB,'BackgroundColor',[1 0.65 0.65]);
			throw(testeBReal);
		else
			set(handles.eB,'BackgroundColor','white');
			
			if ~(b>a)
				set(handles.eA,'BackgroundColor',[1 0.65 0.65]);
				set(handles.eB,'BackgroundColor',[1 0.65 0.65]);
				throw(testeBA);
			else
				set(handles.eA,'BackgroundColor','white');
				set(handles.eB,'BackgroundColor','white');
				
				if ~(isscalar(n)&&(mod(n,1) == 0)&&n>0)
					set(handles.eN,'BackgroundColor',[1 0.65 0.65]);
					throw(testeNInteiro);
 				else
					set(handles.eN,'BackgroundColor','white');
				end
			end
		end
	end

	Escolha01=get(handles.bgFormulasINumerica,'SelectedObject');
	EscolhaFG=find([handles.rTrapezios,handles.rSimpson]==Escolha01);
	switch EscolhaFG
		case 1
			sol = DI_RTrapezios(f,a,b,n);
		case 2
			sol = DI_RSimpson(f,a,b,n);
	end
	
	set(handles.stSolucao,'String',num2str(sol));
	
	% Integral soluçao exata
	sExata=int(f(sym('x')),a,b);
	if ~isscalar(sExata)
		sExata=0;
	end
	set(handles.stSolExata,'String',char(sExata));
	% Integral solução aproximada
	sAproximada=integral(f,a,b);
	if ~isscalar(sAproximada)
		sAproximada=0;
	end
	set(handles.stSolAprox,'String',num2str(sAproximada));
	
	
catch Me
	errordlg(Me.message,'ERRO','modal');
end


% --- Executes on button press in pbGrafico.
function pbGrafico_Callback(hObject, eventdata, handles)
% hObject    handle to pbGrafico (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
MyAtualizarGrafico(handles);

% --- Função auxiliar associada ao botão Atualizar.
function MyAtualizarGrafico(handles)
% handles estrutura de dados com as handles para os objetos...
syms x;
strF=get(handles. tFuncao,'String');
f=@(x) eval(vectorize(char(strF)));
df=diff(f(x));
dfdx=@(x) eval(vectorize(char(df)));

a=str2num(get(handles.eA,'String'));
b=str2num(get(handles.eB,'String'));
n=str2num(get(handles.eN,'String'));

testeAReal=MException('MATLAB:MyAtualizar:badAReal','Introduza um número real em "a"!');
testeBReal=MException('MATLAB:MyAtualizar:badBReal','Introduza um número real em "b"!');
testeBA=MException('MATLAB:MyAtualizar:badBA','Introduza em "a" um número inferior a "b"!');
testeNInteiro=MException('MATLAB:MyAtualizar:badNInteiro','Introduza um número inteiro positivo em "n"!');

try
	if ~(isscalar(a)&&isreal(a))
		set(handles.eA,'BackgroundColor',[1 0.65 0.65]);
		throw(testeAReal);
	else
		set(handles.eA,'BackgroundColor','white');
		
		if ~(isscalar(b)&&isreal(b))
			set(handles.eB,'BackgroundColor',[1 0.65 0.65]);
			throw(testeBReal);
		else
			set(handles.eB,'BackgroundColor','white');
			
			if ~(b>a)
				set(handles.eA,'BackgroundColor',[1 0.65 0.65]);
				set(handles.eB,'BackgroundColor',[1 0.65 0.65]);
				throw(testeBA);
			else
				set(handles.eA,'BackgroundColor','white');
				set(handles.eB,'BackgroundColor','white');
				
				if ~(isscalar(n)&&(mod(n,1) == 0)&&n>0)
					set(handles.eN,'BackgroundColor',[1 0.65 0.65]);
					throw(testeNInteiro);
 				else
					set(handles.eN,'BackgroundColor','white');
				end
			end
		end
	end

	Escolha01=get(handles.bgFormulasINumerica,'SelectedObject');
	EscolhaFG=find([handles.rTrapezios,handles.rSimpson]==Escolha01);
	switch EscolhaFG
		case 1
			sol = DI_RTrapezios(f,a,b,n);
		case 2
			sol = DI_RSimpson(f,a,b,n);
	end
	
	set(handles.stSolucao,'String',num2str(sol));
	
	if (strcmp(get(handles.figureIntegracaoNumerica,'Visible'),'on'))
		h=(b-a)/n;
		x=a:h:b;
		y=dfdx(x);

		% fechar o poligono 
		xx=[x,x(end),x(1)];
		yy=[y,0,0];
		figure(1);
		plot(x,y,'k','linewidth',2);
		hold on;
		fill(xx,yy,[0.65 1 0.65]);
		hold off;
	end
	
	% Integral soluçao exata
	sExata=int(f(sym('x')),a,b);
	if ~isscalar(sExata)
		sExata=0;
	end
	set(handles.stSolExata,'String',char(sExata));
	% Integral solução aproximada
	sAproximada=integral(f,a,b);
	if ~isscalar(sAproximada)
		sAproximada=0;
	end
	set(handles.stSolAprox,'String',num2str(sAproximada));
	
	
catch Me
	errordlg(Me.message,'ERRO','modal');
end


% --------------------------------------------------------------------
function mPrint_Callback(hObject, eventdata, handles)
% hObject    handle to mPrint (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
syms x;
strF=get(handles. tFuncao,'String');
f=@(x) eval(vectorize(char(strF)));
df=diff(f(x));
dfdx=@(x) eval(vectorize(char(df)));

a=str2num(get(handles.eA,'String'));
b=str2num(get(handles.eB,'String'));
n=str2num(get(handles.eN,'String'));

testeAReal=MException('MATLAB:MyAtualizar:badAReal','Introduza um número real em "a"!');
testeBReal=MException('MATLAB:MyAtualizar:badBReal','Introduza um número real em "b"!');
testeBA=MException('MATLAB:MyAtualizar:badBA','Introduza em "a" um número inferior a "b"!');
testeNInteiro=MException('MATLAB:MyAtualizar:badNInteiro','Introduza um número inteiro positivo em "n"!');

try
	if ~(isscalar(a)&&isreal(a))
		set(handles.eA,'BackgroundColor',[1 0.65 0.65]);
		throw(testeAReal);
	else
		set(handles.eA,'BackgroundColor','white');
		
		if ~(isscalar(b)&&isreal(b))
			set(handles.eB,'BackgroundColor',[1 0.65 0.65]);
			throw(testeBReal);
		else
			set(handles.eB,'BackgroundColor','white');
			
			if ~(b>a)
				set(handles.eA,'BackgroundColor',[1 0.65 0.65]);
				set(handles.eB,'BackgroundColor',[1 0.65 0.65]);
				throw(testeBA);
			else
				set(handles.eA,'BackgroundColor','white');
				set(handles.eB,'BackgroundColor','white');
				
				if ~(isscalar(n)&&(mod(n,1) == 0)&&n>0)
					set(handles.eN,'BackgroundColor',[1 0.65 0.65]);
					throw(testeNInteiro);
 				else
					set(handles.eN,'BackgroundColor','white');
				end
			end
		end
	end

	Escolha01=get(handles.bgFormulasINumerica,'SelectedObject');
	EscolhaFG=find([handles.rTrapezios,handles.rSimpson]==Escolha01);
	switch EscolhaFG
		case 1
			sol = DI_RTrapezios(f,a,b,n);
			legPrint = 'RTrapezios';
		case 2
			sol = DI_RSimpson(f,a,b,n);
			legPrint = 'RSimpson';
	end
	
	set(handles.stSolucao,'String',num2str(sol));
	
	% Integral soluçao exata
	sExata=int(f(sym('x')),a,b);
	if ~isscalar(sExata)
		sExata=0;
	end
	set(handles.stSolExata,'String',char(sExata));
	% Integral solução aproximada
	sAproximada=integral(f,a,b);
	if ~isscalar(sAproximada)
		sAproximada=0;
	end
	set(handles.stSolAprox,'String',num2str(sAproximada));
	
	%% escrever dados no excel
	Filename='TabelaIntegral.xlsx';
	sheet = legPrint;
	xlswrite(Filename,{strF},sheet,'B4');
	xlswrite(Filename,{num2str(a)},sheet,'B5');
	xlswrite(Filename,{num2str(b)},sheet,'D5');
	xlswrite(Filename,{num2str(n)},sheet,'F5');
	xlswrite(Filename,{num2str(sol)},sheet,'B7');
	winopen(Filename);
	%%
	
	clc;
	
catch Me
	errordlg(Me.message,'ERRO','modal');
	clc;
end


% --------------------------------------------------------------------
function mClose_Callback(hObject, eventdata, handles)
% hObject    handle to mClose (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
SN=questdlg('Quer fechar?','SAIR','Sim','Não','Sim');
if(strcmp(SN,'Sim'))
	close(handles.figureIntegracaoNumerica);
end
