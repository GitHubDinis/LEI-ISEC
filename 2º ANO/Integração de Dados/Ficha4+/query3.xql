xquery version "1.0";

<ocupacoes>
{
for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/Ficha4/escritores.xml")//escritor
let $lista := $x/ocupacoes/ocupacao
order by $x/@nome
return <escritor nome = '{$x/@nome}'>
		{$x/nome_completo}
		<ocupacoes num = '{count($lista)}'>
		{
			for $ocup in $lista
			order by $ocup
			return $ocup
		}
		</ocupacoes>
	</escritor>
}
</ocupacoes>