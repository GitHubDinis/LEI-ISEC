using System.ComponentModel.DataAnnotations;

namespace PWEB_2324.Models
{
    public class Manager
    {
        public string Id { get; set; }

        [Display(Name = "Nome", Prompt = "Introduza o nome!")]
        [Required(ErrorMessage = "Indique o nome!")]
        public string Nome { get; set; }

        [Display(Name = "Locador", Prompt = "Introduza a locador!")]
        [Required(ErrorMessage = "Descreva a Locador!")]
        public int LocadorId { get; set; }
    }
}
