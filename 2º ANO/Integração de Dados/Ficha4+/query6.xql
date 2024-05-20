xquery version "1.0";

<juntar>
{
for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/Ficha4/escritores.xml")//escritor, $y in doc("C:/Users/Utilizador/Documents/NetBeansProjects/Ficha4/escritores_b.xml")//escritor
let $s := number($y/@stock)
where $x/@nome = $y/@nome 
order by $s
return 
	if ($s < 10) then
		<autor nome='{$x/@nome}' stock='{$s}' alerta='sim'></autor>
	else
		<autor nome='{$x/@nome}' stock='{$s}'></autor>
}
</juntar>