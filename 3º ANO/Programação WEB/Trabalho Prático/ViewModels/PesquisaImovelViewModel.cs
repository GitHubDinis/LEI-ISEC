using PWEB_2324.Models;
using System.ComponentModel.DataAnnotations;
using System.Xml.Linq;

namespace PWEB_2324.ViewModels
{
    public class PesquisaImovelViewModel
    {
        public List<Imovel>? ListaDeImoveis { get; set; }
        public int NumResultados { get; set; }
        [Display(Name = "PESQUISA DE Imoveis ...", Prompt = "introduza o texto a pesquisar")]
        public string? TextoAPesquisar { get; set; }

    }
}
