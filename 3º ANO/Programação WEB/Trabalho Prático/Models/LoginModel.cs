using System.ComponentModel.DataAnnotations;

namespace PWEB_2324.Models
{
    public class LoginModel
    {
        [Required(ErrorMessage = "Informe a user name")]
        [Display(Name = "User")]
        public string? UserName { get; set; }
        [Required(ErrorMessage = "Informe a user password")]
        [Display(Name = "Password")]
        [DataType(DataType.Password)]
        public string? Password { get; set; }
        public string? Url { get; set; }
       
    }
}
