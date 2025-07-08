using System.ComponentModel.DataAnnotations.Schema;

namespace MonProjetAPI.Models
{
    public class Student
    {
        [Column("student_id")]
        public int Id { get; set; }
        [Column("first_name")]
        public string ?FirstName { get; set; }
        [Column("last_name")]
        public string ?LastName { get; set; }
        [Column("city")]
        public string ?City { get; set; }
        [Column("state")]
        public string ?State { get; set; }
        [Column("email")]
        public string ?Email { get; set; }
    }
} 