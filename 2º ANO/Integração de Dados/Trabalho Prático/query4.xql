xquery version "1.0";

declare variable $v := xs:decimal(replace(doc("C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/input.xml")/input/text(), '%', ''));

for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/factos.xml")//pais
where xs:decimal(replace($x/crescimento, '%', '')) > $v
order by $x/@nome
return ('Nome: ', data($x/@nome), '&#10;')